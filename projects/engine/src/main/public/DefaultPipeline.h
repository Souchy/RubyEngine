#pragma once

#include "Ui.h"
#include "Window.h"
#include "resources/Material.h"
#include "shaders/Shader.h"
#include "util/Math.h"
#include "util/MeshVao.h"
#include <flecs.h>

class Pipeline {
public:
    virtual void init(flecs::world &world) = 0;
    virtual void systemInputs(flecs::world &world, flecs::entity_t phase) = 0;
    virtual void systemUpdateLogic(flecs::world &world, flecs::entity_t phase) = 0;
    virtual void systemUpdatePhysic(flecs::world &world, flecs::entity_t phase) = 0;
    virtual void systemRenderDepth(flecs::world &world, flecs::entity_t phase) = 0;
    virtual void systemRenderColor(flecs::world &world, flecs::entity_t phase) = 0;
    virtual void systemRenderMesh(flecs::world &world) = 0;
    virtual void systemRenderUi(flecs::world &world, flecs::entity_t phase) = 0;
    virtual void systemRenderWindow(flecs::world &world, flecs::entity_t phase) = 0;
};

class DefaultPipeline : public Pipeline {
public:
    flecs::query<Transform3d, MeshVao, Material> renderables;
    flecs::system renderMeshSystem;

    virtual void init(flecs::world &world) override {
        // ----- Pipeline
        ecs_entity_t Physics = ecs_new_w_id(world, EcsPhase);
        ecs_entity_t RenderingDepth = ecs_new_w_id(world, EcsPhase);
        ecs_entity_t RenderingColor = ecs_new_w_id(world, EcsPhase);
        ecs_entity_t RenderingUi = ecs_new_w_id(world, EcsPhase);
        ecs_entity_t RenderWindow = ecs_new_w_id(world, EcsPhase);

        // Phases can (but don't have to) depend on other phases which forces ordering
        ecs_add_pair(world, Physics, EcsDependsOn, EcsOnUpdate);
        ecs_add_pair(world, RenderingDepth, EcsDependsOn, Physics);
        ecs_add_pair(world, RenderingColor, EcsDependsOn, RenderingDepth);
        ecs_add_pair(world, RenderingUi, EcsDependsOn, RenderingColor);
        ecs_add_pair(world, RenderWindow, EcsDependsOn, RenderingUi);

        // ----- Systems
        systemRenderMesh(world);
        {
            // Only once instance
            systemInputs(world, flecs::PreUpdate);
            systemUpdateLogic(world, flecs::OnUpdate);
            systemUpdatePhysic(world, Physics);
        }
        {
            // For each light
            systemRenderDepth(world, RenderingDepth);
            // For each camera / viewport
            systemRenderColor(world, RenderingColor);
        }
        {
            // Only once instance
            systemRenderUi(world, RenderingUi);
            systemRenderWindow(world, RenderWindow);
        }
    }

    virtual void systemInputs(flecs::world &world, flecs::entity_t phase) override {
        world.system<Window>("Inputs")
            .term_at(0)
            .singleton()
            .kind(phase) //
            .each([](flecs::iter &it, size_t i, Window &w) {
                if (glfwGetKey(w.m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                    glfwSetWindowShouldClose(w.m_window, true);
                // if (!m_imGuiActive)
                // {
                // 	m_camera.keybordEvents(m_window, delta_time);
                // }
            });
    }

    virtual void systemUpdateLogic(flecs::world &world, flecs::entity_t phase) override {
        world.system<Transform3d, Velocity>("UpdateLogic")
            .kind(phase)
            .each([](flecs::iter &it, size_t i, Transform3d &trans, const Velocity &vel) {
                auto mat = glm::translate(trans.value, vel.value * it.delta_time());
                trans.value = mat;
            });
    }

    virtual void systemUpdatePhysic(flecs::world &world, flecs::entity_t phase) override {
        world.system<Transform3d, Velocity>("UpdatePhysics")
            .kind(phase)
            .each([](flecs::iter &it, size_t i, Transform3d &trans, const Velocity &vel) {
            });
    }

    virtual void systemRenderDepth(flecs::world &world, flecs::entity_t phase) override {
        world.system<Window, Shader>("RenderPass_Depth")
            .kind(phase)
            .term_at(0)
            .singleton()
            .each([](flecs::iter &it, size_t i, const Window &w, const Shader &shader) {
                // glViewport(0, 0, 1024, 1024);
                // glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
                // glEnable(GL_CULL_FACE);
                // glCullFace(GL_FRONT);
                // glClear(GL_DEPTH_BUFFER_BIT);

                // glUseProgram(shader.programId());

                // // renderNode(root);
                // renderMeshSystem.run();

                // glFinish();
                // glBindFramebuffer(GL_FRAMEBUFFER, 0);
            });
    }

    virtual void systemRenderColor(flecs::world &world, flecs::entity_t phase) override {
        // world.system<MeshVao, Shader>("RenderPass_Sky").kind(phase) //
        //     .run([](const MeshVao& vao, const Shader& shader) {
        //         glDisable(GL_DEPTH_TEST);
        //         glBindVertexArray(vao.vaoId);
        //         //  skycubemap
        //         glUseProgram(shader.programId());
        //         // Activez les unités de texture
        //         shader.setMat3(m_skyShaderUniform.viewMatrixCiel, glm::mat3(m_camera->viewMatrix()));
        //         shader.setMat4(m_skyShaderUniform.projectionMatrixCiel, m_camera->projectionMatrix());
        //         // glBindTextureUnit(3, textSky.skyDomeTextureID);
        //         glBindTextureUnit(3, textSky.jourTextureID);
        //         glBindTextureUnit(4, textSky.nuitTextureID);
        //         glDrawElements(GL_TRIANGLES, vao.indexSize, GL_UNSIGNED_INT, 0);
        //         glEnable(GL_DEPTH_TEST);
        //     });

        world.system<Window, Shader>("RenderPass_Color")
            .kind(phase) //
            .term_at(0)
            .singleton()
            .each([this](flecs::iter &it, size_t i, const Window &w, const Shader &shader) {
                // glBindFramebuffer(GL_FRAMEBUFFER, fbo);

                // // 2. then render scene as normal with shadow mapping (using depth map)
                glViewport(0, 0, w.fbo->width, w.fbo->height);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);

                // Render objects
                glUseProgram(shader.programId());
                // glBindTextureUnit(0, *depthMap); // Bind shadow map to texture unit 0

                // Idk if I should use the System or the Query. System is multithreaded.
                // renderNode(root);
                // this->renderMeshSystem.run();
                this->renderables
                    .each([](flecs::iter &it, size_t i, const Transform3d &trans, const MeshVao &mesh, const Material &mat) {
                        auto e = it.entity(i);
                        // render cubes
                        glm::mat4 worldTransform = Math::computeWorldTransform(e);

                        mat.shader->setMat4(10, worldTransform); // worldMatrix
                        // camera
                        // auto view = it.world().get<CameraView3d>();
                        // auto pers = it.world().get<CameraPerspective3d>();
                        auto cam = it.world().get<Camera3d>();
                        mat.shader->setMat4(11, cam->view);       // viewMatrix
                        mat.shader->setMat4(12, cam->projection); // projectionMatrix
                        mat.shader->setVec3(13, cam->pos);        // camPos

                        glBindVertexArray(mesh.vaoId);
                        glDrawElements(mat.MODE, mesh.indexSize, GL_UNSIGNED_INT, nullptr);
                    });

                // glBindFramebuffer(GL_FRAMEBUFFER, 0);
            });
    }

    virtual void systemRenderMesh(flecs::world &world) override {
        this->renderables = world.query_builder<Transform3d, MeshVao, Material>()
                                .cached()
                                .query_flags(EcsQueryMatchEmptyTables)
                                .build();
        this->renderMeshSystem = world
                                     .system<Transform3d, MeshVao, Material>("RenderMesh")
                                     .kind(0) // //  .multi_threaded()
                                     .each([](flecs::iter &it, size_t i, const Transform3d &trans, const MeshVao &mesh, const Material &mat) {
                                         auto e = it.entity(i);
                                         // render cubes
                                         glm::mat4 worldTransform = Math::computeWorldTransform(e);

                                         mat.shader->setMat4(10, worldTransform); // worldMatrix
                                         // camera
                                         // auto view = it.world().get<CameraView3d>();
                                         // auto pers = it.world().get<CameraPerspective3d>();
                                         auto cam = it.world().get<Camera3d>();
                                         mat.shader->setMat4(11, cam->view);       // viewMatrix
                                         mat.shader->setMat4(12, cam->projection); // projectionMatrix
                                         mat.shader->setVec3(13, cam->pos);        // camPos

                                         glBindVertexArray(mesh.vaoId);
                                         glDrawElements(mat.MODE, mesh.indexSize, GL_UNSIGNED_INT, nullptr);
                                     });
    }

    virtual void systemRenderUi(flecs::world &world, flecs::entity_t phase) override {
        world.system<Window, std::shared_ptr<Ui>>("RenderUi_Imgui")
            .kind(phase) //
            .term_at(0)
            .singleton()
            .each([](flecs::iter &it, size_t i, const Window &w, std::shared_ptr<Ui> ui) {
                // Select root node by default
                // if (getSelectedNode() == nullptr)
                //     setSelectedNode(root);

                // Start the Dear ImGui frame
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                flecs::entity root = it.world().lookup("root");
                ui->draw(root);
                // this->renderHierarchy(root);
                // this->renderNodeProperties(root);

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            });
        // world.system<UiTag, Transform3d, Material>("RenderUi_Controls")
        //     .kind(RenderingUi) //
        //     .each([](flecs::iter &it, size_t i, UiTag &ui, const Transform3d &trans, const Material &mat) {
        //     });
    }

    virtual void systemRenderWindow(flecs::world &world, flecs::entity_t phase) override {
        world.system<Window>("Window")
            .term_at(0)
            .singleton()
            .kind(phase)
            .each([](flecs::iter &it, size_t i, const Window &w) {
                // Show rendering and get events
                glfwSwapBuffers(w.m_window);
                // m_imGuiActive = ImGui::IsAnyItemActive();
                glfwPollEvents();
            });
    }
};

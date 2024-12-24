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
    virtual void systemRenderUi(flecs::world &world, flecs::entity_t phase) = 0;
    virtual void systemRenderWindow(flecs::world &world, flecs::entity_t phase) = 0;
};

class DefaultPipeline : public Pipeline {
public:
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
        world.system<std::shared_ptr<Window>>("Inputs")
            .term_at(0)
            .singleton()
            .kind(phase) //
            .each([](flecs::iter &it, size_t i, std::shared_ptr<Window> &w) {
                if (glfwGetKey(w->m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                    glfwSetWindowShouldClose(w->m_window, true);
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
        world.system<std::shared_ptr<Window>, Shader>("RenderPass_Depth")
            .kind(phase)
            .term_at(0)
            .singleton()
            .each([](flecs::iter &it, size_t i, const std::shared_ptr<Window> &w, const Shader &shader) {
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
        world.system<std::shared_ptr<Viewport>, Camera3d, flecs::query<Transform3d, MeshVao, Material>>("RenderPass_Color")
            .kind(phase) //
            .each([this](flecs::iter &it, size_t i, const std::shared_ptr<Viewport> &vp, const Camera3d &cam, const flecs::query<Transform3d, MeshVao, Material> &renderables) {
                auto shader = it.world().get<Shader>();

                glViewport(vp->x, vp->y, vp->width, vp->height);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glClearColor(vp->clearColor.r, vp->clearColor.g, vp->clearColor.b, vp->clearColor.a);

                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);

                glUseProgram(shader->programId());

                // Render all entities with the view camera
                renderables
                    .each([cam](flecs::iter &it, size_t i, const Transform3d &trans, const MeshVao &mesh, const Material &mat) {
                        auto e = it.entity(i);
                        // render cubes
                        glm::mat4 worldTransform = Math::computeWorldTransform(e);

                        mat.shader->setMat4(10, worldTransform); // worldMatrix
                        mat.shader->setMat4(11, cam.view);       // viewMatrix
                        mat.shader->setMat4(12, cam.projection); // projectionMatrix
                        mat.shader->setVec3(13, cam.pos);        // camPos

                        glBindVertexArray(mesh.vaoId);
                        glDrawElements(mat.MODE, mesh.indexSize, GL_UNSIGNED_INT, nullptr);
                    });
            });
    }

    virtual void systemRenderUi(flecs::world &world, flecs::entity_t phase) override {
        world.system<std::shared_ptr<Window>, std::shared_ptr<Ui>>("RenderUi_Imgui")
            .kind(phase) //
            .term_at(0)
            .singleton()
            .each([](flecs::iter &it, size_t i, const std::shared_ptr<Window> &w, std::shared_ptr<Ui> ui) {
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
        world.system<std::shared_ptr<Window>>("Window")
            .term_at(0)
            .singleton()
            .kind(phase)
            .each([](flecs::iter &it, size_t i, const std::shared_ptr<Window> &w) {
                // Show rendering and get events
                glfwSwapBuffers(w->m_window);
                // m_imGuiActive = ImGui::IsAnyItemActive();
                glfwPollEvents();
            });
    }
};

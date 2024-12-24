/*
 * This source file was generated by the Gradle 'init' task
 */

#include <App.h>
#include <iostream>
#include <stdlib.h>

int main() {
    RubyEngine::Greeter greeter;
    std::cout << greeter.greeting() << "!!!!!!!!" << std::endl;

    Ruby *ruby = new Ruby();
    ruby->init();

    App app;
    app.init(ruby);

    ruby->start();

    return 0;
}

void App::init(Ruby *ruby) {
    // ---------- Window
    WindowSize ws;
    ws.width = 1280;
    ws.height = 720;

    std::shared_ptr<Window> window = std::make_shared<Window>();
    // Window window;
    if (window->initialize("Ruby", ws) != 0) {
        return;
    }
    window->onResize = [ruby](int width, int height) {
        WindowSize w = {width, height};
        ruby->world.set<WindowSize>(w);
    };
    ruby->world.set<std::shared_ptr<Window>>(window);
    ruby->world.set<WindowSize>(ws);

    // ---------- Views
    auto viewQuery = ruby->world
                         .query_builder<std::shared_ptr<Viewport>, Camera3d>()
                         .cached()
                         .query_flags(EcsQueryMatchEmptyTables)
                         .build();
    // Update View on Window resize
    ruby->world
        .observer<WindowSize>()
        .event(flecs::OnSet)
        .each([&](WindowSize &ws) {
            // viewQuery.each([ws](std::shared_ptr<Viewport> &vp, Camera3d &cam) {
            //     vp->resize(ws.width, ws.height);
            // });
        });

    // Define View
    {
        // Camera
        // Z+ is towards the screen. Z- is away.
        auto camPos = glm::vec3(0, 5, 10);
        auto camTarget = glm::vec3(0.0f);
        auto camUp = glm::vec3(0.0f, 1.0f, 0.0f);
        auto fov = glm::radians(45.0f);
        Camera3d cam;
        cam.pos = camPos;
        cam.projection = glm::perspective(fov, 16.f / 9.f, 0.1f, 300.0f);
        cam.view = glm::lookAt(camPos, camTarget, camUp);

        // Viewport
        std::shared_ptr<PercentViewport> vp = std::make_shared<PercentViewport>();
        vp->xPercentOfWidth = 0.5f;
        vp->yPercentOfHeight = 0.0f;
        vp->widthPercentOfWidth = 0.5f;
        vp->heightPercentOfHeight = 1.0f;
        vp->clearColor = glm::vec4(0.2f, 0.0f, 0.1f, 1.0f);
        vp->resize(ws.width, ws.height);

        // View world
        // QueryWorld3d query;
        auto renderables = ruby->world.query_builder<Transform3d, MeshVao, Material>()
                                .cached()
                                .query_flags(EcsQueryMatchEmptyTables)
                                .build();
        // Entity View = Camera + Viewport
        ruby->world.entity("view1").set<std::shared_ptr<Viewport>>(vp).set<Camera3d>(cam).set<flecs::query<Transform3d, MeshVao, Material>>(renderables);
    }

    // ---------- Pipeline

    // EditorPipeline pipeline;
    // DefaultPipeline pipeline;
    // pipeline.init(ruby->world);
    ruby->pipeline = std::make_shared<DefaultPipeline>();
    ruby->pipeline->init(ruby->world);

    // ---------- UI
    std::shared_ptr<Ui> ui = std::make_shared<AppUi>();
    ruby->world.set<std::shared_ptr<Ui>>(ui);

    // ---------- Shaders
    auto exepath = Files::getCurrentPath();
    auto dir = exepath.substr(0, exepath.find_last_of("\\/"));

    bool success = true;
    auto shader = new Shader();
    success &= shader->addShaderFromSource(GL_VERTEX_SHADER, dir + "/res/base.vert");
    success &= shader->addShaderFromSource(GL_FRAGMENT_SHADER, dir + "/res/base.frag");
    success &= shader->link();
    if (!success) {
        std::cerr << "Error when loading main shader\n";
        return;
    }
    ruby->world.set<Shader>(*shader);

    // ---------- Entities
    {
        Mesh *cube = Cube::generate();
        MeshVao cubeBuffer = MeshVao::createMeshBuffers(cube);
        Mesh *gizmo = Gizmo::generate();
        MeshVao gizmoBuffer = MeshVao::createMeshBuffers(gizmo);
        Material mat;
        mat.shader = shader;
        Material mat_lines;
        mat_lines.MODE = GL_LINES;
        mat_lines.shader = shader;

        ruby->world.entity("root").scope([&] {
            Transform3d tr1;
            tr1.value = glm::mat4(1.0f);
            flecs::entity parent = ruby->world.entity("parent");
            parent.set<Transform3d>(tr1);
            parent.set<Mesh>(*cube);
            parent.set<MeshVao>(cubeBuffer);
            parent.set<Material>(mat);

            // parent.scope([&]
            {
                Transform3d tr2;
                tr2.value = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0, 0));
                flecs::entity child = ruby->world.entity("child").child_of(parent);
                child.set<Transform3d>(tr2);
                child.set<Mesh>(*cube);
                child.set<MeshVao>(cubeBuffer);
                child.set<Material>(mat);

                Transform3d tr3;
                tr3.value = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.0f, 0.0f));
                // tr3.value = glm::scale(tr3.value, glm::vec3(4.0f, 1.0, 2.0f));
                flecs::entity grandchild = ruby->world.entity("grandchild").child_of(child);
                grandchild.set<Transform3d>(tr3);
                grandchild.set<Mesh>(*cube);
                grandchild.set<MeshVao>(cubeBuffer);
                grandchild.set<Material>(mat);
            }
            // );
            // parent.scope([&]
            {
                Transform3d tr2;
                tr2.value = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0, 0));
                flecs::entity child2 = ruby->world.entity("child2").child_of(parent);
                child2.set<Transform3d>(tr2);
                child2.set<Mesh>(*cube);
                child2.set<MeshVao>(cubeBuffer);
                child2.set<Material>(mat);

                Transform3d tr3;
                tr3.value = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.0f, 0.0f));
                flecs::entity grandchild2 = ruby->world.entity("grandchild2").child_of(child2);
                grandchild2.set<Transform3d>(tr3);
                grandchild2.set<Mesh>(*gizmo);
                grandchild2.set<MeshVao>(gizmoBuffer);
                grandchild2.set<Material>(mat_lines);
            }
            // );
        } //
        );
    }
}

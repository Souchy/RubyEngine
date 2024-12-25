#pragma once

#include <Ui.h>
#include <flecs.h>
#include <imgui.h>
#include <Window.h>
#include <components/Components.h>
#include <components/WorldQuery.h>
#include <components/3d/Components3d.h>

class AppUi : public Ui
{
public:
    std::shared_ptr<Fbo> selectedFbo = nullptr;
    flecs::query<std::shared_ptr<Fbo>> viewQuery;

    void init(flecs::entity root) override
    {
        viewQuery = root.world() // ruby->world
                        .query_builder<std::shared_ptr<Fbo>>()
                        .cached()
                        .query_flags(EcsQueryMatchEmptyTables)
                        .build();
    }

    void draw(flecs::entity root) override
    {
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetStyle().IndentSpacing * 0.5f); // Set smaller indent

        ImGui::Begin("Hierarchy");
        drawTree(root);
        ImGui::End();

        ImGui::Begin("Properties");
        drawProperties(selectedEntity);
        ImGui::End();

        ImGui::Begin("Scene");
        drawScene(root);
        ImGui::End();

        ImGui::Begin("Filesystem");
        drawFilesystem();
        ImGui::End();

        ImGui::PopStyleVar(); // Restore indent
    }

    void drawScene(flecs::entity root) override
    {
        // TODO replace with selected Fbo (could be the whole window, one of the viewports/cam, the physics, the depthmap, etc)

        viewQuery.each([this](flecs::entity view, std::shared_ptr<Fbo> &fbo)
                       {
                           // Draw viewport
                           // ImGui::Text("Fbo: %s", view.name().c_str());
                           bool isSelected = (selectedFbo == fbo);
                           if (ImGui::RadioButton(view.name().c_str(), isSelected))
                           {
                               selectedFbo = fbo;
                           }
                           // ImGui::Text("Camera: %s", cam.name.c_str());
                           // ImGui::Text("Query: %s", query.name.c_str());
                           // ImGui::Text("Viewport: %d, %d, %d, %d", vp->x, vp->y, vp->width, vp->height);
                           // ImGui::Text("Clear Color: %f, %f, %f, %f", vp->clearColor.r, vp->clearColor.g, vp->clearColor.b, vp->clearColor.a);
                       });

        if (selectedFbo == nullptr)
        {
            auto w = *root.world().get<std::shared_ptr<Window>>();
            selectedFbo = w->fbo;
        }
        if (selectedFbo == nullptr)
        {
            return;
        }
        ImGui::Image(selectedFbo->texture, ImVec2(selectedFbo->width, selectedFbo->height), ImVec2(0, 1), ImVec2(1, 0));
    }

    void drawProperties(flecs::entity entity) override
    {
        if (!entity)
        {
            return;
        }
        ImGui::Text("Name: %s", entity.name().c_str());

        // entity.has<Transform3d>([this](Transform3d& transform) {
        //     ImGui::Text("Position: %f, %f, %f", transform.value[3][0], transform.value[3][1], transform.value[3][2]);
        // });

        // entity.each([this](flecs::id id) {
        //     if (id.is_component()) {
        //         const char* component_name = id.name().c_str();
        //         ImGui::Text("Component: %s", component_name);
        //         // You can add more detailed component-specific rendering here
        //     }
        // });
    }

    void drawFilesystem() override
    {
    }
};

#pragma once

#include "components/3d/Components3d.h"

class Ui
{
public:
    flecs::entity selected;
    virtual void draw(flecs::entity root)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetStyle().IndentSpacing * 0.5f); // Set smaller indent
        ImGui::Begin("Hierarchy");
        drawTree(root);
        ImGui::End();

        ImGui::Begin("Properties");
        drawProperties(selected);
        ImGui::End();
        ImGui::PopStyleVar(); // Restore indent
    }

    void drawTree(flecs::entity entity)
    {

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanFullWidth;
        if (ImGui::TreeNodeEx(entity.name().c_str(), flags))
        {
            // entity.children(&drawTree);
            if (ImGui::IsItemClicked())
            {
                selected = entity;
            }
            entity.children([this](flecs::entity child)
                            { drawTree(child); });
            ImGui::TreePop();
        }
    }
    void drawProperties(flecs::entity entity)
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
};

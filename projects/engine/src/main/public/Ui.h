#pragma once

#include "components/3d/Components3d.h"
#include "components/Components.h"
#include <flecs.h>
#include <imgui.h>

class Ui {
public:
    flecs::entity selected;
    
    virtual ~Ui() = default;                   // Virtual destructor

    virtual void draw(flecs::entity root) = 0;

    virtual void drawTree(flecs::entity entity, int depth = 0) {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanFullWidth;

        ImGui::PushID(entity.id());
        bool open = ImGui::TreeNodeEx(entity.name().c_str(), flags);
        // Selection
        if (ImGui::IsItemClicked()) {
            selected = entity;
        }
        // Draw vertical lines
        if (depth > 0) {
            ImDrawList *draw_list = ImGui::GetWindowDrawList();
            ImVec2 pos = ImGui::GetCursorScreenPos();
            float line_height = ImGui::GetTextLineHeight();
            float line_x = pos.x;
            float line_y1 = pos.y - line_height - 2;
            float line_y2 = line_y1 + line_height;
            draw_list->AddLine(ImVec2(line_x, line_y1), ImVec2(line_x, line_y2), IM_COL32(200, 200, 200, 255));
        }
        // Children
        if (open) {
            entity.children([this, depth](flecs::entity child) { drawTree(child, depth + 1); });
            ImGui::TreePop();
        }
        ImGui::PopID();
    }

    virtual void drawProperties(flecs::entity entity) {
        if (!entity) {
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

    virtual void drawScene(const Fbo *fbo) {
    }
    
    virtual void drawFilesystem() {
    }
};

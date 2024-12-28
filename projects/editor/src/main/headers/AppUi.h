#pragma once

#include <Ui.h>
#include <flecs.h>
#include <imgui.h>
#include <Window.h>
#include <resources/Material.h>

class AppUi : public Ui {
public:
    void draw(flecs::entity root) override {
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetStyle().IndentSpacing * 0.5f); // Set smaller indent

        ImGui::Begin("Hierarchy");
        drawTree(root);
        ImGui::End();

        ImGui::Begin("Properties");
        drawProperties(selected);
        ImGui::End();

        ImGui::Begin("Scene");
        auto w = root.world().get<Window>();
        // drawScene(w->fbo);
        ImGui::End();

        ImGui::Begin("Filesystem");
        drawFilesystem();
        ImGui::End();

        ImGui::PopStyleVar(); // Restore indent
    }

    void drawScene(const Fbo *fbo) override {
        // ImGui::Image(fbo->texture, ImVec2(fbo->width, fbo->height));
    }

    void drawProperties(flecs::entity entity) override
    {
        if (!entity)
        {
            return;
        }
        ImGui::Text("Name: %s", entity.name().c_str());

        entity.each([entity](flecs::id id) {
            if(id.is_entity()) {
                auto component = id.entity();
                ImGui::TextColored(ImVec4(1, 0, 1, 1), "Entity: %s", component.name().c_str());
                if (component == flecs::type_id<Transform3d>()) {
                    auto transform = entity.get_mut<Transform3d>();
                    // ImGui::Text("Position: %f, %f, %f", transform->value[3][0], transform->value[3][1], transform->value[3][2]);
                    
                    auto p = transform->getPositionArray();
                    if(ImGui::DragFloat3("Position", p.data(), 0.1f, -1000.0f, 1000.0f)) {
                        transform->setPositionArray(p);
                    }
                    auto r = transform->getRotationArray();
                    if(ImGui::DragFloat3("Rotation", r.data(), 0.1f, 0.0f, 360.0f)) {
                        transform->setRotationArray(r);
                    }
                    auto s = transform->getScaleArray();
                    if(ImGui::DragFloat3("Scale", s.data(), 0.1f, -100.0f, 100.0f)) {
                        transform->setScaleArray(s);
                    }
                }
                if(component == flecs::type_id<Material>()) {
                    auto material = entity.get<Material>();
                    // ImGui::Text("ProgramId %s", material->shader->programId());
                    // ImGui::Text("Material: %s", material->MODE);
                }
            }
            if (id.is_pair()) {
                auto slot = id.first();
                auto component = id.second();
                const char* slot_name = slot.name().c_str();
                const char* component_name = component.name().c_str();
                ImGui::Text("Pair: %s = %s", slot_name, component_name);
                // Add more component-specific rendering here
            }
            ImGui::Separator();
        });
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

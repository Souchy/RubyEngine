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
                    auto transform = entity.get<Transform3d>();
                    ImGui::Text("Position: %f, %f, %f", transform->value[3][0], transform->value[3][1], transform->value[3][2]);
                }
                if(component == flecs::type_id<Material>()) {
                    auto material = entity.get<Material>();
                    // ImGui::Text("ProgramId %s", material->shader->programId());
                    // ImGui::Text("Material: %s", material->MODE);
                }
                if(component == flecs::type_id<Position>()) {
                    auto position = entity.get<Position>();
                    // ImGui::Text("Position: %f, %f, %f", position->value.x, position->value.y, position->value.z);
                    float p[3] = {position->value.x, position->value.y, position->value.z};
                    if(ImGui::DragFloat3("Position", p, 0.01f)) {
                        Position s;
                        s.value = glm::vec3(p[0], p[1], p[2]);
                        entity.set<Position>(s);
                    }
                }
                if(component == flecs::type_id<Scale>()) {
                    auto scale = entity.get<Scale>();
                    // ImGui::Text("Scale: %f, %f, %f", scale->value.x, scale->value.y, scale->value.z);
                    // float* p = &scale->value.x;
                    float p[3] = {scale->value.x, scale->value.y, scale->value.z};
                    if(ImGui::DragFloat3("Scale", p, 0.01f)) {
                        Scale s;
                        s.value = glm::vec3(p[0], p[1], p[2]);
                        entity.set<Scale>(s);
                    }
                }
                if(component == flecs::type_id<Rotation>()) {
                    auto rotation = entity.get<Rotation>();
                    // ImGui::Text("Rotation: %f, %f, %f", rotation->value.x, rotation->value.y, rotation->value.z);
                    // ImGui::DragFloat3("Rotation", &rotation->value.x, 0.01f, -360.0f, 360.0f);
                    float p[3] = {rotation->value.x, rotation->value.y, rotation->value.z};
                    if(ImGui::DragFloat3("Rotation", p, 0.01f, -360.0f, 360.0f)) {
                        Rotation s;
                        s.value = glm::vec3(p[0], p[1], p[2]);
                        entity.set<Rotation>(s);
                    }
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

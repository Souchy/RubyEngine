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
                ImGui::TextColored(ImVec4(1, 0, 1, 1), "Component: %s", component.name().c_str());

                auto ty = component.type();
                auto tyid = component.type_id();

                void* componentValue = entity.get_mut(tyid);
                if(!componentValue) {
                    return;
                }
                if(component != flecs::type_id<Transform3d>()) {
                    return;
                } 
                Transform3d* transforma = entity.get_mut<Transform3d>();
                Transform3d* transformb = (Transform3d*) componentValue;

                {
                    auto tv = rttr::type::get(componentValue);
                    auto typeName1 = component.type_id().name().c_str();
                    auto typeName = "Transform3d*";
                    auto propertyName = "position";
                    auto obj = componentValue;
                    // Get the type of the object
                    rttr::type t = rttr::type::get_by_name(typeName);
                    if (!t.is_valid()) {
                        std::cerr << "Invalid type: " << typeName << std::endl;
                        return;
                    }

                    // Create an instance from the void* object
                    rttr::instance inst = rttr::instance((Transform3d*) obj);

                    // Get the property by its name
                    rttr::property prop = t.get_property(propertyName);
                    if (!prop.is_valid()) {
                        std::cerr << "Invalid property: " << propertyName << std::endl;
                        return;
                    }

                    // Get the value of the property
                    rttr::variant var = prop.get_value(inst);
                    if (!var.is_valid()) {
                        std::cerr << "Failed to get property value: " << propertyName << std::endl;
                        return;
                    }

                    // Print the value (assuming the property is of type glm::vec3 for this example)
                    if (var.is_type<glm::vec3>()) {
                        glm::vec3 value = var.get_value<glm::vec3>();
                        // std::cout << "Property value: (" << value.x << ", " << value.y << ", " << value.z << ")" << std::endl;
                    } else {
                        std::cerr << "Unsupported property type" << std::endl;
                    }
                }

                // auto cv = *componentValue;
                auto tra = componentValue;
                // auto asd = rttr::rttr_cast<Transform3d>(componentValue);
                rttr::instance inst = rttr::instance((void*) (Transform3d*) componentValue);
                auto typ = inst.get_derived_type();

                rttr::type ta1 = rttr::type::get(componentValue); 
                rttr::type ta2 = rttr::type::get(component);
                auto t = rttr::type::get_by_name(component.type_id().name().c_str());
                if (!t.is_valid()) {
                    return; // Skip if type is not valid
                }
                std:: cout << "Type: " << t.get_name() << std::endl;

                rttr::property proa = t.get_property("position");
                auto var1 = proa.get_value(inst);
                auto isvalid = var1.is_valid();
                
                for (auto& prop : t.get_properties()) {
                    // std::cout << "Property name: " << prop.get_name() 
                    //     << ", Type: " << prop.get_type().get_name() << std::endl;
                    auto variant = prop.get_value(inst);
                    if (variant.is_valid()) {
                        if (prop.get_type() == rttr::type::get<glm::vec3>()) {
                            auto val = variant.get_value<glm::vec3>();
                            if (ImGui::DragFloat3(prop.get_name().data(), &val[0], 0.1f, -1000.0f, 1000.0f)) {
                                prop.set_value(inst, val);
                            }
                        }
                    }
                }
                /*
                if (component == flecs::type_id<Transform3d>()) {
                    auto transform = entity.get_mut<Transform3d>();
                    // ImGui::Text("Position: %f, %f, %f", transform->value[3][0], transform->value[3][1], transform->value[3][2]);
                    
                    rttr::type t = rttr::type::get<Transform3d>();
                    for (auto& prop : t.get_properties()) {
                        // std::cout << "Property name: " << prop.get_name() 
                        //     << ", Type: " << prop.get_type().get_name() << std::endl;
                        if (prop.get_type() == rttr::type::get<glm::vec3>()) {
                            auto variant = prop.get_value(transform);
                            auto val = variant.get_value<glm::vec3>();
                            if(ImGui::DragFloat3(prop.get_name().data(), &val[0], 0.1f, -1000.0f, 1000.0f)) {
                                prop.set_value(transform, val);
                            }
                        }
                    }
                */
            }
            // if (id.is_pair()) {
            //     auto slot = id.first();
            //     auto component = id.second();
            //     const char* slot_name = slot.name().c_str();
            //     const char* component_name = component.name().c_str();
            //     ImGui::Text("Pair: %s = %s", slot_name, component_name);
            //     // Add more component-specific rendering here
            // }
            ImGui::Separator();
        });
    }

    void drawFilesystem() override
    {
    }
};

#pragma once

#include <Ui.h>
#include <Window.h>
#include <flecs.h>
#include <imgui.h>

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
        // auto w = root.world().get<Window>();
        // drawScene(w->fbo);
        ImGui::End();

        ImGui::Begin("Filesystem");
        drawFilesystem();
        ImGui::End();

        ImGui::PopStyleVar(); // Restore indent
    }

    void drawScene(const Fbo *fbo) override {
        // ImGui::BeginMenu();
        // ImGui::MenuItem("Scene", NULL, false, false);
        // ImGui::EndMenu();

        static const char *items[]{"One", "Two", "three"};
        static int Selecteditem = 0;
        if (ImGui::Combo("MyCombo", &Selecteditem, items, IM_ARRAYSIZE(items))) {
            // choose fbo to render
        }

        // ImGui::Image(fbo->texture, ImVec2(fbo->width, fbo->height));
    }

    void drawFilesystem() override {
    }
};

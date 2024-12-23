#pragma once

#include <Ui.h>
#include <flecs.h>
#include <imgui.h>

class AppUi : public Ui {
public:
    // void draw() override;
    void draw(flecs::entity root) override {
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetStyle().IndentSpacing * 0.5f); // Set smaller indent

        ImGui::Begin("Hierarchy");
        drawTree(root);
        ImGui::End();

        ImGui::Begin("Properties");
        drawProperties(selected);
        ImGui::End();

        ImGui::Begin("Scene");
        drawScene();
        ImGui::End();

        ImGui::PopStyleVar(); // Restore indent
    }
    void drawScene() override {
        // ImGui::Image((void *)(intptr_t)texture, ImVec2(800, 600));
    }
};

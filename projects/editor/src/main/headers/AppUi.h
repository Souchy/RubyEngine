#pragma once

#include <Ui.h>
#include <flecs.h>
#include <imgui.h>
#include <Window.h>

class AppUi : public Ui
{
public:
    void draw(flecs::entity root) override
    {
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetStyle().IndentSpacing * 0.5f); // Set smaller indent

        ImGui::Begin("Hierarchy");
        drawTree(root);
        ImGui::End();

        ImGui::Begin("Properties");
        drawProperties(selected);
        ImGui::End();

        ImGui::Begin("Scene");
        auto w = *root.world().get<std::shared_ptr<Window>>();
        drawScene(w->fbo);
        ImGui::End();

        ImGui::Begin("Filesystem");
        drawFilesystem();
        ImGui::End();

        ImGui::PopStyleVar(); // Restore indent
    }

    void drawScene(const Fbo *fbo) override
    {
        // TODO replace with selected Fbo (could be the whole window, one of the viewports/cam, the physics, the depthmap, etc)
        if (fbo == nullptr)
        {
            return;
        }
        ImGui::Image(fbo->texture, ImVec2(fbo->width, fbo->height), ImVec2(0, 1), ImVec2(1, 0));
    }

    void drawFilesystem() override
    {
    }
};

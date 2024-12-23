#pragma once

#include <Ui.h>
#include <imgui.h>
#include <flecs.h>

class AppUi : public Ui {
public:
    // void draw() override;
    virtual void draw(flecs::entity root) override {
        ImGui::Begin("App Ui");
        bool show;
        ImGui::Checkbox("Activate Normal map", &show);
        ImGui::End();
    }
};

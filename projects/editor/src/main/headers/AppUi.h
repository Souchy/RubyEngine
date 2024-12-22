#pragma once

#include <Ui.h>
#include <imgui.h>

class AppUi : public Ui {
public:
    // void draw() override;
    virtual void draw() override {
        ImGui::Begin("App Ui");
        bool show;
        ImGui::Checkbox("Activate Normal map", &show);
        ImGui::End();
    }
};

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <components/Components.h>
#include <functional>

class Window {
public:
    // settings
    std::function<void(int, int)> onResize;
    Fbo* fbo = nullptr;

    // GLFW Window
    GLFWwindow *m_window = nullptr;

    int initialize(const char *title, WindowSize ws);
    void InitializeCallback();
    // Callback to intersept GLFW calls
    void FramebufferSizeCallback(int width, int height);
    void MouseButtonCallback(int button, int action, int mods);
    void CursorPositionCallback(double xpos, double ypos);
    int RenderLoop();
};

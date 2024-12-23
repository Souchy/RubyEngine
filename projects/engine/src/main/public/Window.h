#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <components/Components.h>

class Window {
public:
    // settings
    // unsigned int m_windowWidth = 1700;
    // unsigned int m_windowHeight = 900;
    // WindowSize* size;
    Fbo* fbo = nullptr;

    // GLFW Window
    GLFWwindow *m_window = nullptr;

    int initialize(const char *title, Fbo* fbo);
    void InitializeCallback();
    // Callback to intersept GLFW calls
    void FramebufferSizeCallback(int width, int height);
    void MouseButtonCallback(int button, int action, int mods);
    void CursorPositionCallback(double xpos, double ypos);
    int RenderLoop();
};

/*
 * This source file was generated by the Gradle 'init' task
 */

#include "RubyEngine.h"

flecs::world Ruby::world;

std::string RubyEngine::Greeter::greeting() {
    return std::string("Hello, World!");
}


void Ruby::init() {
    // ---------- Window
    Fbo* fbo;
    fbo->width = 1700;
    fbo->height = 900;
    Window window;
    if (window.initialize("Ruby", fbo) != 0) {
        return;
    }
    world.set<Window>(window);

    // Init GL properties (?)
    glPointSize(10.0f);
    glEnable(GL_DEPTH_TEST);

    // ---------- Systems
    world.set_threads(4);
}

void Ruby::start() {
    // ---------- Engine loop
    float time = (float)glfwGetTime();
    float delta_time = 1.0f / 60.0f;
    while (world.progress(delta_time)) {
        // Compute delta time between two frames
        float new_time = (float)glfwGetTime();
        delta_time = new_time - time;
        time = new_time;
    }
    // ---------- Cleanup
    glfwDestroyWindow(world.get<Window>()->m_window);
    glfwTerminate();
}

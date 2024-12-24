#include <iostream>

#include <Window.h>

int Window::initialize(const char *title, WindowSize ws) {
    // OpenGL version (usefull for imGUI and other libraries)
    const char *glsl_version = "#version 460 core";

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();

    // Request OpenGL 4.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if ACTIVE_DEBUG_CALLBACK
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    m_window = glfwCreateWindow(ws.width, ws.height, title, nullptr, nullptr);
    if (m_window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(m_window);

    InitializeCallback();

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return 2;
    }

    // imGui: create interface
    // ---------------------------------------
    // this->ui = new Ui();
    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Activate debug callback (if needed)
    // -----------------------------
#if ACTIVE_DEBUG_CALLBACK
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        std::cout << "Debug context created\n";
        // initialize debug output
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_FALSE);
        glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DONT_CARE, 0, NULL, GL_TRUE);
    }
#endif

    // Other openGL initialization
    // -----------------------------
    // return InitializeGL();
    
    // Init GL properties (?)
    glPointSize(10.0f);
    glEnable(GL_DEPTH_TEST);
    return 0;
}

void Window::InitializeCallback() {
    glfwSetWindowUserPointer(m_window, reinterpret_cast<void *>(this));
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
        Window *w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
        w->FramebufferSizeCallback(width, height);
    });
    glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods) {
        Window *w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
        w->MouseButtonCallback(button, action, mods);
    });
    glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xpos, double ypos) {
        Window *w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
        w->CursorPositionCallback(xpos, ypos);
    });
}

void Window::FramebufferSizeCallback(int width, int height) {
    // ws->width = width;
    // ws->height = height;

    if(onResize) {
        onResize(width, height);
    } else {
        printf("Resize callback not set\n");
    }
    // fbo->y = 0;
    // fbo->x = width / 2;
    // fbo->width = width / 2;
    // fbo->height = height;
    // glViewport(fbo->x, fbo->y, fbo->width, fbo->height);
    // m_camera.viewportEvents(width, height);
}

void Window::CursorPositionCallback(double xpos, double ypos) {
    // if (!m_imGuiActive)
    // {
    // 	int state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
    // 	m_camera.mouseEvents(glm::vec2(xpos, ypos), state == GLFW_PRESS);
    // }
}

void Window::MouseButtonCallback(int button, int action, int mods) {
    // // selection cube
    // if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mods == GLFW_MOD_CONTROL)
    // {
    // 	double xpos, ypos;
    // 	//getting cursor position
    // 	glfwGetCursorPos(m_window, &xpos, &ypos);

    // 	PerformSelection((int)xpos, (int)ypos);
    // }

    // // selection cube
    // if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mods == GLFW_MOD_SHIFT)
    // {
    // 	double xpos, ypos;
    // 	//getting cursor position
    // 	glfwGetCursorPos(m_window, &xpos, &ypos);
    // 	std::cout << "[DEBUG][TODO] Shift pressed (Face selection)\n";
    // }
}

int Window::RenderLoop() {
    float time = (float)glfwGetTime();
    while (!glfwWindowShouldClose(m_window)) {
        // Compute delta time between two frames
        float new_time = (float)glfwGetTime();
        const float delta_time = new_time - time;
        time = new_time;

        // Check inputs: Does ESC was pressed?
        if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_window, true);
        // if (!m_imGuiActive)
        // {
        // 	m_camera.keybordEvents(m_window, delta_time);
        // }

        // RenderScene(delta_time);
        // RenderImgui();

        // Show rendering and get events
        glfwSwapBuffers(m_window);
        // m_imGuiActive = ImGui::IsAnyItemActive();
        glfwPollEvents();
    }

    // Cleanup
    glfwDestroyWindow(m_window);
    glfwTerminate();

    return 0;
}

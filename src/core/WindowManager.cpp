#include <core/WindowManager.hpp>
#include <iostream>

bool WindowManager::initialize(int width, int height, std::string title) {
    // init glfw
    if (!glfwInit()) {
        std::cerr << "Failled to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // instantiate glfw window
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    // init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glViewport(0, 0, width, height);

    return true;
}

bool WindowManager::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void WindowManager::shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
}


void WindowManager::swapBuffers() const {
    glfwSwapBuffers(window);
}

void WindowManager::pollEvents() const {
    glfwPollEvents();
}

WindowManager::WindowManager() {}
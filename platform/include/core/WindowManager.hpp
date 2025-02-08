#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <tuple>

#include <graphics/Renderer.hpp>

namespace Styx 
{
    class WindowManager
    {
    private:
        GLFWwindow* window;
        WindowManager();
    public:
        static Renderer* renderer;
        static WindowManager& getInstance() {
            static WindowManager instance; // Lazy initialization, thread-safe
            return instance;
        }
        bool initialize(int width, int heigt, std::string title);
        void pollEvents() const;
        void swapBuffers() const;
        bool shouldClose() const;
        void shutdown();
        GLFWwindow* getGLFWWindow();
        void setRenderer(Renderer* renderer);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
            if (width == 0 || height == 0) {
                return;
            }

            auto manager = WindowManager::getInstance();
            manager.onFramebufferSizeChanged(width, height);
        }

        void onFramebufferSizeChanged(int width, int height) {
            // Update the OpenGL viewport and inform the renderer
            glViewport(0, 0, width, height);
            if (this->renderer)
            {
                renderer->updateAspectRatio(width, height);
            }
            else {
                std::cout << "renderer is a nullptr : " << this->renderer << std::endl;
            }

        }
    };
}
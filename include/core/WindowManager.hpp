#if !defined(WINDOW_H)
#define WINDOW_H

#include <3rdparty/glad/glad.h>
#include <3rdparty/GLFW/glfw3.h>
#include <string>
#include <tuple>

#include <graphics/RendererManager.hpp>


#include <dll_export.h>


class DLL_EXPORT WindowManager
{
private:
    GLFWwindow* window;
    WindowManager();
    RendererManager* renderer;
public:
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
    void setRenderer(RendererManager* renderer);
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
        renderer->updateAspectRatio(width, height);
    }
};

#endif // WINDOW_H
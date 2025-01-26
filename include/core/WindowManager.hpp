#if !defined(WINDOW_H)
#define WINDOW_H

#include <3rdparty/glad/glad.h>
#include <3rdparty/GLFW/glfw3.h>
#include <string>

#include <dll_export.h>


class DLL_EXPORT WindowManager
{
private:
    GLFWwindow* window;
    WindowManager();
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
};

#endif // WINDOW_H
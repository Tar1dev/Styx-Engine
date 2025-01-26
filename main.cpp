#include <core/WindowManager.hpp>
#include <graphics/RendererManager.hpp>

int main(int argc, char const *argv[])
{
    auto& wm = WindowManager::getInstance();
    if (!wm.initialize(900, 800, "Game framework")) {
        wm.shutdown();
        return -1;
    }

    auto& renderer = RendererManager::getInstance();

    while (!wm.shouldClose()) {
        renderer.clear();

        renderer.drawTriangle();

        wm.pollEvents();
        wm.swapBuffers();
    }
    
    wm.shutdown();
    return 0;
}

#include <core/WindowManager.hpp>
#include <graphics/RendererManager.hpp>
#include <graphics/Texture2D.hpp>

int main(int argc, char const *argv[])
{
    auto& wm = WindowManager::getInstance();
    if (!wm.initialize(900, 800, "Game framework")) {
        wm.shutdown();
        return -1;
    }

    auto& renderer = RendererManager::getInstance();

    unsigned int box = Texture2D::loadFromFile("./assets/textures/container.jpg");
    unsigned int smile = Texture2D::loadFromFile("./assets/textures/awesomeface.png");

    while (!wm.shouldClose()) {
        renderer.clear();

        renderer.update();

        //renderer.drawTexture(box);
        renderer.drawTexture(smile);

        wm.pollEvents();
        wm.swapBuffers();
    }
    
    wm.shutdown();
    return 0;
}

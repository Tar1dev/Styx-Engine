#include <core/WindowManager.hpp>
#include <graphics/Renderer.hpp>
#include <graphics/Texture2D.hpp>

#include <core/Application.hpp>

#include <game.hpp>

int main(int argc, char const *argv[])
{
    auto& wm = Styx::WindowManager::getInstance();
    if (!wm.initialize(800, 800, "Game framework")) {
        wm.shutdown();
        return -1;
    }

    auto& renderer = Styx::Renderer::getInstance();
    renderer.initialize(800, 800);

    wm.setRenderer(&renderer);

    

    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    Game game;
    game.init();



    while (!wm.shouldClose()) {
        // deltatime calculation
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        game.draw();
        game.update(deltaTime);

        renderer.clear();
        renderer.update();

        wm.pollEvents();
        wm.swapBuffers();
    }
    
    wm.shutdown();
    return 0;
}

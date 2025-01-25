#include <game/Game.hpp>
#include <core/WindowManager.hpp>
#include <graphics/RendererManager.hpp>

void Game::run() {
    EngineFacade engine;

    engine.initialize();

    auto& wm = WindowManager::getInstance();
    auto& renderer = RendererManager::getInstance();

    while (!wm.shouldClose()) {
        renderer.clear();

        renderer.drawTriangle();

        wm.pollEvents();
        wm.swapBuffers();
    }
    
    engine.shutdown();
}
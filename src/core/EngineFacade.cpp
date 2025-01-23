#include <core/EngineFacade.hpp>

bool EngineFacade::initialize() {
    if (!WindowManager::getInstance().initialize(900, 800, "The perfect game engine !")) {
        return false;
    }   
    return true;
}

// Main loop
void EngineFacade::run() {
    auto& wm = WindowManager::getInstance();
    while(!wm.shouldClose())
    {
        glClearColor(0.5, 0.5, 0.5, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        wm.pollEvents();
        wm.swapBuffers();
    }
}

void EngineFacade::shutdown() {
    WindowManager::getInstance().shutdown();
}
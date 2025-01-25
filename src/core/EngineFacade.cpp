#include <core/EngineFacade.hpp>
#include <graphics/ShaderProgramBuilder.hpp>
#include <iostream>

bool EngineFacade::initialize() {
    if (!WindowManager::getInstance().initialize(900, 800, "The perfect game engine !")) {
        return false;
    }
    return true;
}

bool EngineFacade::shouldClose() {
    return WindowManager::getInstance().shouldClose();
}

void EngineFacade::shutdown() {
    WindowManager::getInstance().shutdown();
}
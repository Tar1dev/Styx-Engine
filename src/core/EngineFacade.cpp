#include <core/EngineFacade.hpp>
#include <graphics/ShaderFactory.hpp>
#include <graphics/ShaderProgramBuilder.hpp>

bool EngineFacade::initialize() {
    if (!WindowManager::getInstance().initialize(900, 800, "The perfect game engine !")) {
        return false;
    }   

    ShaderProgramBuilder builder;
    ShaderProgram* shaderProgram = builder
        .setVertexShader("main.frag")
        .setFragmentShader("main.frag")
        .build();
    
    std::cout << "Shader program ID: " << shaderProgram->getProgramID() << std::endl;

    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     0.0f,  0.5f, 0.0f
    // };


    // GLuint VBO;
    // glGenBuffers(1, &VBO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
#include <graphics/RendererManager.hpp>


RendererManager::RendererManager() {
    ShaderProgramBuilder builder;
    shaderProgram = builder
        .setVertexShader("main.vert")
        .setFragmentShader("main.frag")
        .build();

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // Unbind the VAO
}

void RendererManager::clear() {
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RendererManager::drawTriangle() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glUseProgram(shaderProgram->getProgramID());
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}
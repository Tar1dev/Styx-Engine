#include <graphics/RendererManager.hpp>
#include <3rdparty/GLFW/glfw3.h>
#include <3rdparty/stb_image.h>
#include <math.h>
#include <iostream>



RendererManager::RendererManager() {
    // default shaders
    ShaderProgramBuilder builder;
    shaderProgram = builder
        .setVertexShader("./assets/shaders/main.vert")
        .setFragmentShader("./assets/shaders/main.frag")
        .build();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);  

    glBindVertexArray(0); // Unbind the VAO

    stbi_set_flip_vertically_on_load(true);  
}

void RendererManager::clear() {
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RendererManager::update() {
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glUseProgram(shaderProgram->getProgramID());
    glBindVertexArray(VAO);
}

void RendererManager::drawTexture(Texture2D texture, glm::vec2 coords) {
    glm::mat4 trans = texture.getTransform();
    trans = glm::translate(trans, glm::vec3(coords.x, coords.y, 0.0f));

    unsigned int transformLoc = glGetUniformLocation(shaderProgram->getProgramID(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
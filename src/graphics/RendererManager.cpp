#include <graphics/RendererManager.hpp>
#include <3rdparty/GLFW/glfw3.h>
#include <3rdparty/stb_image.h>
#include <math.h>
#include <iostream>

RendererManager::RendererManager() {}

bool RendererManager::initialize(int width, int height) {
    // default shaders
    ShaderProgramBuilder builder;
    shaderProgram = builder
        .setVertexShader("./assets/shaders/main.vert")
        .setFragmentShader("./assets/shaders/main.frag")
        .build();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    const int VAO_size = 9 * sizeof(float);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VAO_size, (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VAO_size, (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture position attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VAO_size, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2); 

    // texture attribute
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, VAO_size, (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0); // Unbind the VAO

    //stbi_set_flip_vertically_on_load(true);     

    camera.projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 100.0f);
    camera.view = glm::translate(camera.view, glm::vec3(0.0f, 0.0f, -2.0f));

    return true;
} 

void RendererManager::clear() {
    glClearColor(0.3, 0.3, 0.3, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RendererManager::update() {
    float vertices[] = {
        // positions                // colors           // texture coords       // texture IDs;
        400.0f,  400.0f, 0.0f,      1.0f, 0.0f, 0.0f,   1.0f, 1.0f,             0.0f, // bottom right
        400.0f, 0.0f, 0.0f,         1.0f, 0.0f, 0.0f,   1.0f, 0.0f,             0.0f, // top right
        0.0f, 400.0f, 0.0f,         1.0f, 0.0f, 0.0f,   0.0f, 1.0f,             0.0f, // bottom left
        0.0f,  0.0f, 0.0f,          1.0f, 0.0f, 0.0f,   0.0f, 0.0f,             0.0f, // top left 


        // positions                // colors           // texture coords       // texture IDs;
        750.0f,  400.0f, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 1.0f,             1.0f, // bottom right
        750.0f, 0.0f, 0.0f,         0.0f, 1.0f, 0.0f,   1.0f, 0.0f,             1.0f, // top right
        400.0f, 400.0f, 0.0f,       0.0f, 1.0f, 1.0f,   0.0f, 1.0f,             1.0f, // bottom left
        400.0f,  0.0f, 0.0f,        0.0f, 1.0f, 0.0f,   0.0f, 0.0f,             1.0f // top left
    };

    unsigned int indices[] = {
        // First Quad
        0, 1, 3, // first triangle
        0, 3, 2, // second triangle

        // Second Quad
        4, 5, 7, // first triangle
        4, 7, 6  // second triangle
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void RendererManager::updateAspectRatio(int width, int height) {
    camera.projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 100.0f);
}

void RendererManager::drawTests(Texture2D texture1, Texture2D texture2, glm::vec2 coords) {
    glUseProgram(shaderProgram->getProgramID());

    glm::mat4 model = texture1.getTransform();
    model = glm::translate(model, glm::vec3(coords.x, coords.y, 0.0f));

    unsigned int modelLoc = glGetUniformLocation(shaderProgram->getProgramID(), "model");
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram->getProgramID(), "projection");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram->getProgramID(), "view");

    unsigned int texturesLoc = glGetUniformLocation(shaderProgram->getProgramID(), "ourTextures");
    int samplers[2] = {0, 1};

    glUniform1iv(texturesLoc, 2, samplers);


    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera.projection));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view));

    glBindVertexArray(VAO);

    glBindTextureUnit(0, texture1.getTextureId());
    glBindTextureUnit(1, texture2.getTextureId());
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    // todo: batch rendering next steps (https://www.youtube.com/watch?v=bw6JsLnx5Jg)
}
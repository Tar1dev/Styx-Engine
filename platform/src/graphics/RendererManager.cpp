#include <graphics/Renderer.hpp>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <math.h>
#include <iostream>

using namespace Styx;

Renderer::Renderer() {
    camera.projection = glm::mat4(1.0f); // Identity matrix
    camera.view = glm::mat4(1.0f);       // Identity matrix
}

bool Renderer::initialize(int width, int height) {
    // default shaders
    ShaderProgramBuilder builder;
    shaderProgram = builder
        .setVertexShader(std::string(RESSOURCES_DIR) + "/shaders/main.vert")
        .setFragmentShader(std::string(RESSOURCES_DIR) + "/shaders/main.frag")
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

void Renderer::clear() {
    glClearColor(0.0, 0.0, 0.0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::updateAspectRatio(int width, int height) {
    camera.projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 100.0f);
}


void Renderer::update() {

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

    

    glUseProgram(shaderProgram->getProgramID());
    int samplers[16] = {};
    for (size_t textureIdx = 0; textureIdx < textures.size(); textureIdx++)
    {
        samplers[textureIdx] = textureIdx;
        glBindTextureUnit(textureIdx, textures[textureIdx]);
    }

    glm::mat4 model = glm::mat4(1.0f);
    unsigned int modelLoc = glGetUniformLocation(shaderProgram->getProgramID(), "model");
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram->getProgramID(), "projection");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram->getProgramID(), "view");
    auto textureLoc = glGetUniformLocation(shaderProgram->getProgramID(), "aTextures");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera.projection));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view));
    glUniform1iv(textureLoc, 16, samplers);
    


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


    // todo: textures batch rendering

    // Clear batch data for next frame
    resetBatchCache();
}

void Renderer::resetBatchCache() {
    vertices.clear();
    indices.clear();
    textures.clear();
    indexOffset = 0;
}


void Renderer::drawTexture(Texture2D texture, glm::vec2 coords) {
    float x = coords.x;
    float y = coords.y;
    float w = 400;
    float h = 400;

    int textureIndex = textures.size();  // Store the current texture index before adding

    textures.push_back(texture.getTextureId());  // Add texture to the list


    float quadVertices[] = {
        // positions  // colors          // texture coords // texture IDs;
        x + w, y + h, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, (float)textureIndex, // bottom right
        x + w, y,     0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, (float)textureIndex, // top right
        x,     y + h, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, (float)textureIndex, // bottom left
        x,     y,     0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, (float)textureIndex  // top left
    };

    unsigned int quadIndices[] = {
        indexOffset, indexOffset + 1, indexOffset + 3,
        indexOffset, indexOffset + 3, indexOffset + 2
    };

    vertices.insert(vertices.end(), std::begin(quadVertices), std::end(quadVertices));
    indices.insert(indices.end(), std::begin(quadIndices), std::end(quadIndices));

    indexOffset += 4;
}
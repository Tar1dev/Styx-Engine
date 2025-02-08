#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <optional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Styx
{
    class Texture2D
    {
    private:
        unsigned int ID;
        glm::mat4 trans;
    public:
        Texture2D(std::optional<std::string> fileName = std::nullopt);
        bool loadFromFile(std::string fileName);
        void applyTransform(glm::mat4 transform);
        glm::mat4 getTransform();
        unsigned int getTextureId();
    };
}
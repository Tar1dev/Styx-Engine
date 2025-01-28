#if !defined(TEXTURE_2D_HPP)
#define TEXTURE_2D_HPP

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <dll_export.h>

class DLL_EXPORT Texture2D
{
private:
    unsigned int ID;
    glm::mat4 trans;
public:
    Texture2D();
    bool loadFromFile(std::string fileName);
    void applyTransform(glm::mat4 transform);
    glm::mat4 getTransform();
    unsigned int getTextureId();
};

#endif // TEXTURE_2D_HPP

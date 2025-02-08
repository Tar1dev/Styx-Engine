#include <graphics/Texture2D.hpp>

using namespace Styx;

Texture2D::Texture2D() {
    trans = glm::mat4(1.0f);
}

bool Texture2D::loadFromFile(std::string fileName) {
    GLenum fileType;
    if(fileName.substr(fileName.find_last_of(".") + 1) == "png") {
        fileType = GL_RGBA;
    } else {
        fileType = GL_RGB;
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, fileType, width, height, 0, fileType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        ID = texture;
        stbi_image_free(data);
        return true;
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
        stbi_image_free(data);
        return false;
    }
};

unsigned int Texture2D::getTextureId() {
    return ID;
}

glm::mat4 Texture2D::getTransform() {
    return trans;
}

void Texture2D::applyTransform(glm::mat4 transform) {
    trans = transform;
}
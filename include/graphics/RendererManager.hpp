#if !defined(RENDERER_MANAGER_HPP)
#define RENDERER_MANAGER_HPP

#include <glad/glad.h>
#include <graphics/ShaderProgramBuilder.hpp>

class RendererManager
{
private:
    RendererManager();
    GLuint VBO, VAO;
    ShaderProgram* shaderProgram;
public:
    static RendererManager& getInstance() {
        static RendererManager instance;
        return instance;
    }

    void clear();
    void drawTriangle();
    bool addShader(std::string vertexShaderSource, std::string fragmentShaderSource);
};


#endif // RENDERER_MANAGER_HPP

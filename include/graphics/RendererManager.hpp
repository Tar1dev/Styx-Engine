#if !defined(RENDERER_MANAGER_HPP)
#define RENDERER_MANAGER_HPP

#include <graphics/ShaderProgramBuilder.hpp>
#include <vector>

class RendererManager
{
private:
    RendererManager();
    GLuint VBO, VAO, EBO;
    ShaderProgram* shaderProgram;
public:
    static RendererManager& getInstance() {
        static RendererManager instance;
        return instance;
    }

    void clear();
    void drawTriangle();
    bool addShader(std::string vertexShaderSourcePath, std::string fragmentShaderSourcePath);
    bool setCurrentShader(ShaderProgram shader);

    void drawTexture(unsigned int texture);

    void update();
};


#endif // RENDERER_MANAGER_HPP

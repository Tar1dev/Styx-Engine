#if !defined(RENDERER_MANAGER_HPP)
#define RENDERER_MANAGER_HPP

#include <graphics/ShaderProgramBuilder.hpp>
#include <graphics/Texture2D.hpp>

#include <dll_export.h>


class DLL_EXPORT RendererManager
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

    void drawTexture(Texture2D texture, glm::vec2 coords);

    void update();
};


#endif // RENDERER_MANAGER_HPP

#if !defined(RENDERER_MANAGER_HPP)
#define RENDERER_MANAGER_HPP

#include <graphics/ShaderProgramBuilder.hpp>
#include <graphics/Texture2D.hpp>

#include <dll_export.h>


typedef struct DLL_EXPORT Camera
{
    glm::mat4 projection;
    glm::mat4 view;
} Camera;


class DLL_EXPORT RendererManager
{
private:
    RendererManager();
    GLuint VBO, VAO, EBO;
    ShaderProgram* shaderProgram;
    Camera camera;
public:
    static RendererManager& getInstance() {
        static RendererManager instance;
        return instance;
    }

    bool initialize(int width, int height);

    void clear();
    void drawTriangle();
    bool addShader(std::string vertexShaderSourcePath, std::string fragmentShaderSourcePath);
    bool setCurrentShader(ShaderProgram shader);

    void drawTests(Texture2D texture, Texture2D, glm::vec2 coords);

    void update();
    void updateAspectRatio(int, int);
};


#endif // RENDERER_MANAGER_HPP

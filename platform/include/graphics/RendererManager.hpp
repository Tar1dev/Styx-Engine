#if !defined(RENDERER_MANAGER_HPP)
#define RENDERER_MANAGER_HPP

#include <graphics/ShaderProgramBuilder.hpp>
#include <graphics/Texture2D.hpp>

#include <dll_export.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


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
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    int indexOffset = 0;
    std::vector<GLuint> textures;
public:
    static RendererManager& getInstance() {
        static RendererManager instance;
        return instance;
    }

    bool initialize(int width, int height);

    void clear();
    bool addShader(std::string vertexShaderSourcePath, std::string fragmentShaderSourcePath);
    bool setCurrentShader(ShaderProgram shader);

    void drawTexture(Texture2D texture, glm::vec2 coords);

    void update();
    void updateAspectRatio(int, int);
};


#endif // RENDERER_MANAGER_HPP

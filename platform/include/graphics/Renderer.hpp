#pragma once

#include <graphics/ShaderProgramBuilder.hpp>
#include <graphics/Texture2D.hpp>

#include <vector>


namespace Styx
{
    typedef struct
    {
        glm::mat4 projection;
        glm::mat4 view;
    } Camera;

    class Renderer
    {
    private:
        Renderer();
        GLuint VBO, VAO, EBO;
        ShaderProgram* shaderProgram;
        Camera camera;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        unsigned int indexOffset = 0;
        std::vector<GLuint> textures;
        void resetBatchCache();
    public:
        static Renderer& getInstance() {
            static Renderer instance;
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
}
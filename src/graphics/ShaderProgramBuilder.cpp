#include <graphics/ShaderProgramBuilder.hpp>
#include <graphics/ShaderFactory.hpp>
#include <utils/shader_reader.h>

ShaderProgramBuilder& ShaderProgramBuilder::setVertexShader(const std::string& filePath) {
    vertexShaderSourcePath = filePath;
    return *this;
}

ShaderProgramBuilder& ShaderProgramBuilder::setFragmentShader(const std::string& filePath) {
    fragmentShaderSourcePath = filePath;
    return *this;
}

ShaderProgram* ShaderProgramBuilder::build() {
    char* vertexShaderSource = readShaderSource(vertexShaderSourcePath);
    char* fragmentShaderSource = readShaderSource(fragmentShaderSourcePath);

    ShaderProgram* shaderProgram = new ShaderProgram();

    shaderProgram->vertexShader = ShaderFactory::createShader(vertexShaderSource, GL_VERTEX_SHADER);
    shaderProgram->fragmentShader = ShaderFactory::createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    if (!shaderProgram->checkShaders()) {
        std::cerr << "Failled to compile shaders !" << std::endl;
        return nullptr;
    }

    shaderProgram->attachShaders();
    shaderProgram->link();
    shaderProgram->cleanShaders();

    return shaderProgram;
}
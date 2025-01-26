#include <graphics/ShaderProgramBuilder.hpp>
#include <graphics/ShaderFactory.hpp>

#include <fstream>
#include <sstream>

char* readShaderSource(std::string file_name) {

    std::ostringstream oss;
    oss << file_name;
    
    std::ifstream vertexShaderSourceStream(oss.str(), std::ios::in | std::ios::binary);

    if (!vertexShaderSourceStream.is_open()) {
        std::cerr << "Error opening the shader source!" << std::endl;
    }

    vertexShaderSourceStream.seekg(0, std::ios::end);
    std::streamsize fileSize = vertexShaderSourceStream.tellg();  // Get file size
    vertexShaderSourceStream.seekg(0, std::ios::beg);

    // Allocate memory for the file content
    char* buffer = new char[fileSize + 1];  // +1 for null terminator (if needed)

    // Read the content of the file into the buffer
    if (vertexShaderSourceStream.read(buffer, fileSize)) {
        // Add a null terminator (in case the file is treated as a C-style string)
        buffer[fileSize] = '\0';
    }

    return buffer;
}


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
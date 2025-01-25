#include <graphics/ShaderProgram.hpp>

ShaderProgram::ShaderProgram(): programID(glCreateProgram()), vertexShader(0), fragmentShader(0) {}

void ShaderProgram::attachShaders() {
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
}

void ShaderProgram::link() {
    glLinkProgram(programID);
}

bool ShaderProgram::checkShaders() {
    if (vertexShader == 0 || fragmentShader == 0) {
        return false;
    }
    return true;
}
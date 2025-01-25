#if !defined(SHADER_FACTORY_HPP)
#define SHADER_FACTORY_HPP

#include <glad/glad.h>
#include <string>
#include <iostream>

class ShaderFactory
{
public:
    static GLuint createShader(const char* src, GLenum type) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
            return 0;
        }

        std::cout << "Shader compiled successfully !" << std::endl;

        return shader;
    }

};

#endif // SHADER_FACTORY_HPP

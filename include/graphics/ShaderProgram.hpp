#if !defined(SHADER_PROGRAM_HPP)
#define SHADER_PROGRAM_HPP

#include <3rdparty/glad/glad.h>
#include <string>

class ShaderProgram
{
private:
    GLuint programID;
    GLuint vertexShader;
    GLuint fragmentShader;
    ShaderProgram();
public:
    GLuint getProgramID() const { return programID; }
    void attachShaders();
    void link();
    bool checkShaders();
    void cleanShaders();
    friend class ShaderProgramBuilder;
};



#endif // SHADER_PROGRAM_HPP

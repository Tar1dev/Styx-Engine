#if !defined(SHADER_PROGRAM_BUILDER_HPP)
#define SHADER_PROGRAM_BUILDER_HPP

#include <graphics/ShaderProgram.hpp>

class ShaderProgramBuilder
{
private:
    std::string vertexShaderSourcePath;
    std::string fragmentShaderSourcePath;

public:
    ShaderProgramBuilder& setVertexShader(const std::string& filePath);
    ShaderProgramBuilder& setFragmentShader(const std::string& filePath);

    ShaderProgram* build();
};



#endif // SHADER_PROGRAM_BUILDER_HPP

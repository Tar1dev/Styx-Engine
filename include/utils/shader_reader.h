#if !defined(SHADER_READER_H)
#define SHADER_READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

char* readShaderSource(std::string file_name) {

    std::ostringstream oss;
    oss << "./assets/shaders/" << file_name;
    
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


#endif // SHADER_READER_H


#version 450 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in float aTexIndex;

out vec3 ourColor;
out vec2 TexCoord;
out float TexIndex;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() 
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    ourColor = aColor;
    TexIndex = aTexIndex;
    TexCoord = aTexCoord; 
}

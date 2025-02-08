#version 450 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in float TexIndex;


uniform sampler2D aTextures[16]; // Support up to 16 texture slots

void main()
{
    int index = int(TexIndex);
    FragColor = texture(aTextures[index], TexCoord);
}

#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in float TexIndex;

uniform sampler2D ourTextures[2];

void main()
{
    //FragColor = texture(ourTexture, TexCoord);
    FragColor = texture(ourTextures[int(TexIndex)], TexCoord);
}
#version 330 core

in vec3 vertexColor;
in vec2 TextCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TextCoord);
}
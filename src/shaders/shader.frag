#version 330 core

// in vec3 ourColor;
in vec2 TextCoord;

out vec4 FragColor;

uniform sampler2D texture01;

void main()
{
    FragColor = texture(texture01, TextCoord);
}
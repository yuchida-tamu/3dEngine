#version 330 core

// in vec3 ourColor;
in vec2 TextCoord;

out vec4 FragColor;

uniform sampler2D texture01;
uniform sampler2D texture02;

void main()
{
    FragColor = mix(texture(texture01, TextCoord), texture(texture02, TextCoord), 0.2);
    //  FragColor = mix(texture(texture01, TextCoord), texture(texture02, TextCoord), 0.2) * vec4(ourColor, 1.0);
}
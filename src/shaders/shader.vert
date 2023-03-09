#version 330 core

layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

// out vec3 ourColor;
out vec2 TextCoord;
out vec3 FragPos;
out vec3 Normal;

uniform vec3 viewPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
     gl_Position = projection * view * model * vec4(aPos, 1.0);
     // ourColor = aColor;
     TextCoord = vec2(aTexCoord.x, aTexCoord.y);
     FragPos = vec3(model * vec4(aPos, 1.0));
     Normal =mat3(transpose(inverse(model))) * aNormal;
}
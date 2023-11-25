#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 nearPoint;
out vec3 farPoint;


uniform vec3 viewPos;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

vec3 unprojectPoint(float x, float y, float z, mat4 view, mat4 projection) {
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main()
{
    nearPoint = unprojectPoint(aPos.x, aPos.y, 0.0, view, projection).xyz; // unprojecting on the near plane
    farPoint = unprojectPoint(aPos.x, aPos.y, 1.0, view, projection).xyz; // unprojecting on the far plane
    
    gl_Position = vec4(aPos, 1.0);
}
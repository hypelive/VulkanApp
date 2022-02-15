#version 450

// do prod in c++ for optimizations
layout(binding = 0) uniform UniformBufferObject
{
    mat4 model;
    mat4 view;
    mat4 proj;
    mat4 mvp;

    vec3 dirLight;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() 
{
    gl_Position = ubo.mvp * vec4(inPosition, 1.0);
    fragColor = vec3(dot(ubo.dirLight, inNormal));
    fragTexCoord = inTexCoord;
}
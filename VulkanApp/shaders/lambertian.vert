#version 450

layout(binding = 0) uniform UniformBufferObject
{
    mat4 model;
    mat4 view;
    mat4 proj;

    mat4 vp;
    mat4 mvp;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec3 fragPosition;

void main() 
{
    vec4 worldPosition = ubo.model * vec4(inPosition, 1.0);
    fragPosition = worldPosition.xyz;
    gl_Position = ubo.vp * worldPosition;

    fragTexCoord = inTexCoord;
    fragNormal = inNormal;
}
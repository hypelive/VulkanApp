#version 450

layout(binding = 0) uniform UniformBufferObject
{
    mat4 model;
    mat4 view;
    mat4 proj;
    mat4 mvp;

    vec3 dirLight;
} ubo;

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;

layout(location = 0) out vec4 outColor;

const vec4 ambientColor = vec4(0.04, 0.04, 0.04, 1);

void main() 
{
    vec3 lighting = vec3(max(0, dot(ubo.dirLight, normalize(fragNormal))));
    outColor = vec4(lighting, 1.0) + ambientColor;
}
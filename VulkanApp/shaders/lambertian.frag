#version 450

#define PI 3.1415926538

layout(binding = 0) uniform UniformBufferObject
{
    mat4 model;
    mat4 view;
    mat4 proj;
    mat4 mvp;

    vec3 dirLight;
} ubo;

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 fragNormal;

layout(location = 0) out vec4 outColor;

const vec4 ambientColor = vec4(0.04, 0.04, 0.04, 1);
const vec3 directionalColor = vec3(0.7, 0.7, 0.0);
const float brdf = 1 / PI;

void main() 
{
    vec3 lighting = directionalColor * max(0, dot(ubo.dirLight, normalize(fragNormal))) * brdf;
    outColor = texture(texSampler, fragTexCoord) * vec4(lighting, 1.0) + ambientColor;
}
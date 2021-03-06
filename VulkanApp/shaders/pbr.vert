#version 450

layout(binding = 0) uniform UniformBufferObject
{
    mat4 view;
    mat4 proj;

    mat4 vp;

    vec4 cameraPosition;
} ubo;

layout(binding = 4) uniform DynamicUniformBufferObject
{
    mat4 model;
} dubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 inNormal;

layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec3 fragPosition;
layout(location = 3) out vec3 fragView;

void main() 
{
    vec4 worldPosition = dubo.model * vec4(inPosition, 1.0);
    fragPosition = worldPosition.xyz;
    gl_Position = ubo.vp * worldPosition;

    fragTexCoord = inTexCoord;

    fragNormal = (dubo.model * vec4(inNormal, 0.0)).xyz;

    fragView = ubo.cameraPosition.xyz - fragPosition;
}
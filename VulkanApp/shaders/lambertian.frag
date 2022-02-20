#version 450

#define PI 3.1415926538

layout(binding = 1) uniform sampler2D texSampler;

struct AmbientLight
{
    vec4 color;
};

const int MAX_DIRECTIONAL_LIGHTS = 4;
struct DirectionalLight
{
    vec4 color;
    vec4 direction;
};

const int MAX_POINT_LIGHTS = 8;
struct PointLight
{
    vec4 color;
    vec4 position;
};

layout(binding = 2, std140) uniform LightSources
{
    AmbientLight ambient;
    DirectionalLight directional[MAX_DIRECTIONAL_LIGHTS];
    int directionalCount;
    PointLight point[MAX_POINT_LIGHTS];
    int pointCount;
} lights;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec3 fragPosition;

layout(location = 0) out vec4 outColor;

const float BRDF = 1 / PI;

void main() 
{
    vec3 lighting = vec3(0.0);
    for (int i = 0; i < lights.directionalCount; i++)
    {
        lighting += lights.directional[i].color.xyz * max(0, dot(lights.directional[i].direction.xyz, normalize(fragNormal))) * BRDF;
    }
    
    for (int i = 0; i < lights.pointCount; i++)
    {
        vec3 pointOffset = lights.point[i].position.xyz - fragPosition;
        float pointIntensity = 1 / (4 * PI * dot(pointOffset, pointOffset));
        lighting += lights.point[i].color.xyz * pointIntensity * max(0, dot(normalize(pointOffset), normalize(fragNormal))) * BRDF;
    }

    outColor = texture(texSampler, fragTexCoord) * vec4(lighting, 1.0) + lights.ambient.color;
    outColor.w = 1.0;
}
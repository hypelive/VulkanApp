#version 450

#define PI 3.1415926538

// point light falloff
#define LINEAR_FALOFF
//#define SQR_FALOFF

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

layout(binding = 3, std140) uniform Material
{
    vec4 F0;
    float alpha;
} material;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec3 fragPosition;
layout(location = 3) in vec3 fragView;

layout(location = 0) out vec4 outColor;

const float SPECULAR_GLOSS = 2.2;
const float SPECULAR_POWER = 0.5;
const vec3 SPECULAR_COLOR = vec3(1.0, 0.5, 1.0);

void main()
{
    vec3 v = normalize(fragView);
    vec3 n = normalize(fragNormal);
    vec3 rho = texture(texSampler, fragTexCoord).xyz;

    vec3 lighting = vec3(0.0);
    for (int i = 0; i < lights.directionalCount; i++)
    {
        vec3 l = lights.directional[i].direction.xyz;
        vec3 r = reflect(-l, n);
        vec3 specular = pow(max(0, dot(r, v)), SPECULAR_GLOSS / 4.0) * SPECULAR_POWER * SPECULAR_COLOR;
        vec3 diffuse = max(0, dot(l, n)) * rho;

        lighting += lights.directional[i].color.xyz * (specular + diffuse);
    }
    
    for (int i = 0; i < lights.pointCount; i++)
    {
        vec3 pointOffset = lights.point[i].position.xyz - fragPosition;
#if defined(LINEAR_FALOFF)
        float pointIntensity = 1 / sqrt(dot(pointOffset, pointOffset));
#elif defined(SQR_FALOFF)
        float pointIntensity = 1 / dot(pointOffset, pointOffset);
#endif

        vec3 l = normalize(pointOffset);
        vec3 r = reflect(-l, n);
        vec3 specular = pow(max(0, dot(r, v)), SPECULAR_GLOSS / 4.0) * SPECULAR_POWER * SPECULAR_COLOR;
        vec3 diffuse = max(0, dot(l, n)) * rho;

        lighting += lights.point[i].color.xyz * pointIntensity * (specular + diffuse);
    }

    outColor = vec4(lighting, 1.0) + lights.ambient.color;
}
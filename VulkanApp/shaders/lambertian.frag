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
layout(location = 3) in vec3 fragView;

layout(location = 0) out vec4 outColor;

const float BRDF = 1.0 / PI;

// To c++
const vec3 F0 = vec3(0.3, 0.4, 0.5);
const float alpha = 0.25;
const float alphaG = 0.25; // sqr user input

void getFresnelReflectance(in vec3 n, in vec3 l, out vec3 reflectance)
{
    // Schlick approximation
    // F(n, l) ≈ F0 + (1 − F0)(1 − (n · l)^5)

    float NdotL = dot(n, l);

    reflectance = F0 + (1 - F0) * pow(1 - max(0, NdotL), 5);
}

void getMaskingShadowing(in vec3 l, in vec3 v, in vec3 m, out float maskingShadowing)
{
    // Smith height-correlated masking-shadowing function
    // G2(l, v, m) = χ+(m · v)χ+(m · l)/(1 + Λ(v) + Λ(l))

    // Λ(roughness) - for CGX is shape-invariant

    float MdotV = dot(m, v);
    float MdotL = dot(m, l);

    float temp = MdotV*MdotV;

    float numerator = float(MdotV > 0 && MdotL > 0);
    float denominator = sqrt(1 + alpha * alpha * (1 - temp) / temp);
    maskingShadowing = numerator / denominator;
}

void getNormalDistribution(in vec3 n, in vec3 m, out float normalDistribution)
{
    // CGX

    float NdotM = dot(n, m);
    float sqrAlpha = alphaG * alphaG;
    
    float temp = 1 + NdotM * NdotM * (sqrAlpha - 1);

    normalDistribution = float(NdotM > 0) * sqrAlpha / (PI * temp * temp);
}

void main()
{
    vec3 v = normalize(fragView);
    vec3 n = normalize(fragNormal);
    // ignore alpha
    vec3 rho = texture(texSampler, fragTexCoord).xyz;

    vec3 lighting = vec3(0.0);
    for (int i = 0; i < lights.directionalCount; i++)
    {
        vec3 l = lights.directional[i].direction.xyz;
        vec3 h = normalize(l + v);
        vec3 F;
        getFresnelReflectance(n, l, F);
        float G;
        getMaskingShadowing(l, v, h, G);
        float D;
        getNormalDistribution(n, h, D);

        vec3 specular = F * G * D / (4 * abs(dot(n, l)) * abs(dot(n, v)));
        vec3 diffuse = (1 - F) * rho / PI;

        lighting += lights.directional[i].color.xyz * max(0, dot(l, n)) * (specular + diffuse);
    }
    
    for (int i = 0; i < lights.pointCount; i++)
    {
        // TODO PBR

        vec3 pointOffset = lights.point[i].position.xyz - fragPosition;
        float pointIntensity = 1 / (4 * PI * dot(pointOffset, pointOffset));
        lighting += lights.point[i].color.xyz * pointIntensity * max(0, dot(normalize(pointOffset), n)) * BRDF;
    }

    outColor = vec4(lighting, 1.0) + lights.ambient.color;
    outColor.w = 1.0;
}
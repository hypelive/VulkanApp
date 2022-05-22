#version 450

#define PI 3.1415926538

// NDF
#define GGX
//#define Beckmann

// G2 calculation
//#define LambdaSqr

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

void getFresnelReflectance(in vec3 n, in vec3 l, out vec3 reflectance)
{
    // Schlick approximation
    // F(n, l) ≈ F0 + (1 − F0)(1 − (n · l)^5)

    float NdotL = dot(n, l);

    reflectance = material.F0.xyz + (1 - material.F0.xyz) * pow(1 - max(0, NdotL), 5);
}

void getMaskingShadowing(in vec3 l, in vec3 v, in vec3 m, out float maskingShadowing)
{
    // Smith height-correlated masking-shadowing function
    // G2(l, v, m) = χ+(m · v)χ+(m · l)/(1 + Λ(v) + Λ(l))

    // Λ(roughness) - for GGX/Beckmann is shape-invariant
    float MdotV = dot(m, v);
    float MdotL = dot(m, l);
    float sqrMdotV = MdotV*MdotV;
    float numerator = float(MdotV > 0 && MdotL > 0);

#if defined(GGX)
    // (9.42)
    float denominator = sqrt(1 + material.alpha * material.alpha * (1 - sqrMdotV) / sqrMdotV);

#elif defined(Beckmann)
    // (9.39)
    float a = MdotV / (material.alpha * sqrt(1 - sqrMdotV));
    float sqrA = a*a;
    float denominator = 1 + 2 * float(a < 1.6) * (1 - 1.259*a + 0.396*sqrA)/(3.535*a + 2.181*sqrA);

#endif

#if defined(LambdaSqr)
    // case G2 = G1 * G1 need to account sqr lambda
    float lambda = (denominator - 1) / 2;
    denominator = denominator + lambda * lambda;

#endif

    maskingShadowing = numerator / denominator;
}

void getNormalDistribution(in vec3 n, in vec3 m, out float normalDistribution)
{
    float NdotM = dot(n, m);
    float sqrAlpha = material.alpha * material.alpha;

#if defined(GGX)
    // (9.41)
    float temp = 1 + NdotM * NdotM * (sqrAlpha - 1);
    normalDistribution = float(NdotM > 0) * sqrAlpha / (PI * temp * temp);

#elif defined(Beckmann)
    // (9.35)
    float sqrNdotM = NdotM*NdotM;
    normalDistribution = float(NdotM > 0) * exp((sqrNdotM - 1)/(sqrAlpha * sqrNdotM)) / (PI * sqrAlpha * sqrNdotM * sqrNdotM);

#endif
}

void getBRDF(in vec3 n, in vec3 v, in vec3 l, vec3 rho, out vec3 value)
{
    vec3 h = normalize(l + v);
    vec3 F;
    getFresnelReflectance(n, l, F);
    float G;
    getMaskingShadowing(l, v, h, G);
    float D;
    getNormalDistribution(n, h, D);

    vec3 specular = F * G * D / (4 * abs(dot(n, l)) * abs(dot(n, v)));
    vec3 diffuse = (1 - F) * rho / PI;

    value = specular + diffuse;
}

void main()
{
    vec3 v = normalize(fragView);
    vec3 n = normalize(fragNormal);
    vec3 rho = texture(texSampler, fragTexCoord).xyz;

    vec3 lighting = vec3(0.0);
    for (int i = 0; i < lights.directionalCount; i++)
    {
        vec3 l = lights.directional[i].direction.xyz;
        vec3 brdf;
        getBRDF(n, v, l, rho, brdf);

        lighting += lights.directional[i].color.xyz * max(0, dot(l, n)) * brdf;
    }
    
    for (int i = 0; i < lights.pointCount; i++)
    {
        vec3 pointOffset = lights.point[i].position.xyz - fragPosition;
        float sqrLen = max(dot(pointOffset, pointOffset), 1.0);
#if defined(LINEAR_FALOFF)
        float pointIntensity = 1 / sqrt(sqrLen);
#elif defined(SQR_FALOFF)
        float pointIntensity = 1 / sqrLen;
#endif

        vec3 l = normalize(pointOffset);
        vec3 brdf;
        getBRDF(n, v, l, rho, brdf);

        lighting += lights.point[i].color.xyz * pointIntensity * max(0, dot(l, n)) * brdf;
    }

    outColor = vec4(lighting, 1.0) + lights.ambient.color;
}
#version 330 core

#define PI 3.14159265358979323846f

out vec4 color;

in vec3 fragPos_CAMSPACE;
in vec2 UV;
in vec4 normal_wrong;
in vec3 fragPos;

struct Material
{
	sampler2D albedo;
	sampler2D roughness;
	sampler2D normalMap;
	bool metallic;
	float IOR;
};

uniform Material mat;

uniform vec3 viewPos;

in mat4 MVP;

vec3 normal;
vec3 normal_CAMSPACE;
vec3 normal_TANSPACE;
vec3 viewVector = normalize(fragPos - viewPos);

vec3 albedoColor;
float roughness;

struct PointLight
{
	vec3 position;
	vec3 color;
	float intensity;
	vec3 ambient;
};

float lerp(float a, float b, float t)
{
	return ((1 - t) * a) + (t * b);
}

vec3 lerp3(vec3 c1, vec3 c2, float t)
{
	return vec3(
	lerp(c1.x, c2.x, t),
	lerp(c1.y, c2.y, t),
	lerp(c1.z, c2.z, t)
	);
}

float sqr(float x)
{
	return x * x;
}

float F(float n1, float n2)
{
	float R0 = sqr((n1 - n2) / (n1 + n2));
	return R0 + ((1 - R0) * pow(1 + dot(viewVector, normal), 5));
}

float GGX_D(vec3 N, vec3 wh, float _roughness)
{
    float a2     = sqr(sqr(_roughness)); // sqr(roughness)
    float NdotH2  = sqr(max(dot(normal, wh), 0));
    return a2 / (PI * sqr(NdotH2 * (a2 - 1) + 1));
}

float G1(float NdotV, float _roughness)
{
    float k = sqr(_roughness + 1) / 8.f;
    return NdotV / (NdotV * (1 - k) + k);
}
float SMITH_G(vec3 wi, vec3 wo, float _roughness)
{	
    return G1(max(dot(normal, wo), 0), _roughness) * G1(max(dot(normal, wi), 0), roughness);
}

float attenuation(vec3 wi, float d2, PointLight l)
{
	float cosTheta = max(0, dot(normal, wi));
	return cosTheta / d2;
}

float specularLightContribution(vec3 wi, vec3 wo, vec3 wh, float fresnel, PointLight l)
{
	float D = GGX_D(normal, wh, roughness);       
	float G = SMITH_G(wi, wo, roughness);	
	float cosTheta = max(0, dot(normal, wi));
	float BRDF = (D * fresnel * G) / max(0.01, 4 * max(dot(normal, wo), 0) * max(dot(normal, wi), 0));
	return BRDF;
}

vec3 fragColor;

void addLightContribution(float fresnel, PointLight l)
{			
	vec3 wi = l.position - fragPos;
	float d2 = dot(wi, wi);
	wi = normalize(wi);
	vec3 wo = -viewVector;
	vec3 wh = normalize(wi + wo);

	float diffuseAmount = (1 - fresnel);
	float specularAmount = fresnel;

	vec3 lightColor = l.color * l.intensity * attenuation(wi, d2, l);
	float specularColor = specularLightContribution(wi, wo, wh, fresnel, l);

	if(mat.metallic)
		fragColor += specularColor * lightColor * albedoColor / PI;
	else
		fragColor += (diffuseAmount * albedoColor + specularAmount * specularColor) * lightColor / PI;
}

vec3 tonemap(vec3 _color)
{
	return _color / (_color + vec3(1, 1, 1));
}

#define LightingMode unsigned int

#define Unlit        0
#define Lit          1
#define Normals      2
#define White        3

void main()
{
	LightingMode mode = Lit;

//	normal_TANSPACE = texture(normalMap, UV).rgb;
//    normal = normalize(normal * 2.0 - 1.0);   

	normal = vec3(normal_wrong);
	normal_CAMSPACE = vec3(MVP * normal_wrong);

	if(dot(normal, viewVector) > 0) 
	{
		normal *= -1;
		normal_CAMSPACE *= -1;
	}

	albedoColor = texture(mat.albedo, UV).rgb;
	roughness = texture(mat.roughness, UV).r;

	switch(mode)
	{
	case Lit:			
		float n1 = 1;
		float n2 = mat.IOR;

		float R = F(n1, n2);

		fragColor = vec3(0);

		for(int i = 0; i < 10; i++)
		{		
			for(int j = 0; j < 10; j++)
			{		
				PointLight light;
				light.position = vec3((i - 5) * 2, (j - 5) * 2, 3);
				light.intensity = 100;
				light.color = vec3(1);//vec3(i / 10.f, (10 - i) / 10.f, i / 10.f);
				light.ambient = vec3(0.f);

				addLightContribution(R, light);
			}
		}

		fragColor = tonemap(fragColor);

		break;

	case Unlit:
		fragColor = albedoColor;
		break;

	case White:
		fragColor = vec3(1);
		break;

	case Normals:
		fragColor = vec3((normal + vec3(1, 1, 1)) / 2);
		break;

	default:
		fragColor = vec3(0);
		break;
	}

	color = vec4(fragColor, 1);
}
#version 460 core

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	sampler2D texture_normal1;
	sampler2D texture_normal2;
	sampler2D texture_height1;
	sampler2D texture_height2;
	//镜面反射半径
	float shininess;
};

struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform Light m_Light;
uniform PointLight m_PointLight;
uniform Material m_Material;

in vec3 u_viewPos;
//in vec3 u_Normal;
in vec2 u_TexCoord;
in vec3 u_WorldPos;
//in mat3 TBN;

in vec3 tangentLightPos;
in vec3 tangentViewPos;
in vec3 tangentFragPos;

vec4 CalcuDirLight(Light light, vec3 normal, vec3 viewdir);
vec4 CalcuPointLight(PointLight light, vec3 normal, vec3 point, vec3 viewdir);

out vec4 color;
void main()
{

	//vec3 norm		= normalize(u_Normal);
	vec3 norm = texture(m_Material.texture_height1, u_TexCoord).rgb;
    // Transform normal vector to range [-1,1]
    norm = normalize(norm * 2.0 - 1.0);   
	//norm = normalize(TBN * norm);

	//vec3 viewDir	= normalize(u_ViewPos - u_WorldPos);
	vec3 viewDir	= normalize(tangentViewPos - tangentFragPos);

	//计算定向光
	vec4 outPutColor = CalcuDirLight(m_Light, norm, viewDir);
	outPutColor += CalcuPointLight(m_PointLight, norm, tangentFragPos, viewDir);

	if(outPutColor.a < 0.1)
		discard;
	color = outPutColor;
	
}

vec4 CalcuDirLight(Light light, vec3 normal, vec3 viewdir)
{
	/*
	 * 平行光
	*/
	//计算漫反射
	//vec3 lightDir	= normalize(-light.direction);
	vec3 lightDir = normalize(tangentLightPos - tangentFragPos);
	float diff		= max(dot(normal, lightDir), 0.f);
	vec4 diffuse	= diff * texture(m_Material.texture_diffuse1, u_TexCoord) * vec4(light.diffuse,1.f);

	//计算高光
	//观察向量（从表面指向光源）
	vec3 reflectDir		= reflect(-lightDir, normal);		//反射法线
	vec3 halfwayDir		= normalize(lightDir + viewdir);
	float spec			= pow(max(dot(normal, halfwayDir), 0.0), m_Material.shininess);
	vec4 specular		= texture(m_Material.texture_specular1, u_TexCoord) * spec * vec4(light.specular,1.0);

	//计算环境光
	vec4 ambient	= texture(m_Material.texture_diffuse1, u_TexCoord) * vec4(light.ambient,1.0);

	return (ambient + diffuse + specular);
}

vec4 CalcuPointLight(PointLight light, vec3 normal, vec3 point, vec3 viewdir)
{
	/*
	 * 点光源
	*/
	//计算漫反射
	vec3 lightDir	= normalize(light.position - point);
	float diff		= max(dot(normal, lightDir), 0.f);
	vec4 diffuse	= diff * texture(m_Material.texture_diffuse1, u_TexCoord) * vec4(light.diffuse, 1.f);

	//计算环境光
	vec4 ambient		= texture(m_Material.texture_diffuse1, u_TexCoord) * vec4(light.ambient, 1.f);

	//计算高光
	//观察向量（从表面指向光源）
	//vec3 reflectDir		= reflect(-lightDir, normal);		//反射法线
	vec3 halfwayDir		= normalize(lightDir + viewdir);
	float spec			= pow(max(dot(normal, halfwayDir), 0.0), m_Material.shininess);
	//float spec			= pow(max(dot(viewdir, reflectDir), 0.0), m_Material.shininess);
	vec4 specular		= texture(m_Material.texture_specular1, u_TexCoord) * spec * vec4(light.specular, 1.f);

	//计算光线衰减
	float distance		= length(light.position - point);
	float attenuation	= 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
	ambient				*= attenuation;
	diffuse				*= attenuation;
	specular			*= attenuation;

	return (ambient + diffuse + specular);
}
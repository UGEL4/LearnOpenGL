#version 460 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
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

struct SpotLight{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;
};


in vec2 u_TexCoord;
in vec3 u_Normal;
in vec3 u_WorldPos;

//观察者位置
uniform vec3 viewPos;

uniform Material m_Material;
uniform Light m_Light;

#define NR_POINT_LIGHTS 1
uniform PointLight m_PointLights[NR_POINT_LIGHTS];

uniform SpotLight m_SpolitLight;

out vec4 color;

vec3 CalcuDirLight(Light light, vec3 normal, vec3 viewdir);
vec3 CalcuPointLight(PointLight light, vec3 normal, vec3 point, vec3 viewdir);
vec3 CalcuSpotLight(SpotLight light, vec3 normal, vec3 point, vec3 viewdir);

void main()
{
	 vec3 norm		= normalize(u_Normal);
	 vec3 viewDir	= normalize(viewPos - u_WorldPos);

	 //计算定向光
	 vec3 outPutColor	= CalcuDirLight(m_Light, norm, viewDir);
	 //计算点光
	 for(int i = 0; i < NR_POINT_LIGHTS; i++)
	 {
		 outPutColor += CalcuPointLight(m_PointLights[i], norm, u_WorldPos, viewDir);
	 }
	 //计算聚光
	 outPutColor +=CalcuSpotLight(m_SpolitLight, norm, u_WorldPos, viewDir);

	 color = vec4(outPutColor, 1.f);
}

vec3 CalcuDirLight(Light light, vec3 normal, vec3 viewdir)
{
	/*
	 * 平行光
	*/
	//计算漫反射
	vec3 lightDir	= normalize(-light.direction);
	float diff		= max(dot(normal, lightDir), 0.f);
	vec3 diffuse	= diff * vec3(texture(m_Material.diffuse, u_TexCoord)) * light.diffuse;

	//计算高光
	//观察向量（从表面指向光源）
	vec3 reflectDir		= reflect(-lightDir, normal);		//反射法线
	float spec			= pow(max(dot(viewdir, reflectDir), 0.0), m_Material.shininess);
	vec3 specular		= vec3(texture(m_Material.specular, u_TexCoord)) * spec * light.specular;

	//计算环境光
	vec3 ambient	= vec3(texture(m_Material.diffuse, u_TexCoord)) * light.ambient;

	return (ambient + diffuse + specular);
}

vec3 CalcuPointLight(PointLight light, vec3 normal, vec3 point, vec3 viewdir)
{
	/*
	 * 点光源
	*/
	//计算漫反射
	vec3 lightDir	= normalize(light.position - point);
	float diff		= max(dot(normal, lightDir), 0.f);
	vec3 diffuse	= diff * vec3(texture(m_Material.diffuse, u_TexCoord)) * light.diffuse;

	//计算环境光
	vec3 ambient		= vec3(texture(m_Material.diffuse, u_TexCoord)) * light.ambient;

	//计算高光
	//观察向量（从表面指向光源）
	vec3 reflectDir		= reflect(-lightDir, normal);		//反射法线
	float spec			= pow(max(dot(viewdir, reflectDir), 0.0), m_Material.shininess);
	vec3 specular		= vec3(texture(m_Material.specular, u_TexCoord)) * spec * light.specular;

	//计算光线衰减
	float distance		= length(light.position - point);
	float attenuation	= 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
	ambient				*= attenuation;
	diffuse				*= attenuation;
	specular			*= attenuation;

	return (ambient + diffuse + specular);
}

vec3 CalcuSpotLight(SpotLight light, vec3 normal, vec3 point, vec3 viewdir)
{
	/*
	 * 聚光
	*/
	//计算环境光
	vec3 ambient = vec3(texture(m_Material.diffuse, u_TexCoord)) * light.ambient;

	//计算漫反射
	vec3 lightDir = normalize(-light.direction);
	float diff		= max(dot(normal, lightDir), 0.f);
	vec3 diffuse	= diff * vec3(texture(m_Material.diffuse, u_TexCoord)) * light.diffuse;

	//计算高光
	//观察向量（从表面指向光源）
	vec3 reflectDir		= reflect(-lightDir, normal);		//反射法线
	float spec			= pow(max(dot(viewdir, reflectDir), 0.0), m_Material.shininess);
	vec3 specular		= vec3(texture(m_Material.specular, u_TexCoord)) * spec * light.specular;

	//计算光线衰减
	float distance		= length(light.position - point);
	float attenuation	= 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
	ambient				*= attenuation;
	diffuse				*= attenuation;
	specular			*= attenuation;

	//聚光核心计算
	//片段指向光源的向量
	vec3 dir = normalize(light.position - point);
	//角度
	float theta = dot(dir, normalize(-light.direction));
	//平滑处理
	float intensity = clamp((theta - light.outerCutOff) / (light.cutOff - light.outerCutOff), 0.f, 1.f);
	//不对环境光做出影响
	//ambient		*= intensity;
	diffuse		*= intensity;
	specular	*= intensity;

	return (ambient + diffuse + specular);
}
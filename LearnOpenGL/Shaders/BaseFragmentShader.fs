#version 460 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	//���淴��뾶
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

//�۲���λ��
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

	 //���㶨���
	 vec3 outPutColor	= CalcuDirLight(m_Light, norm, viewDir);
	 //������
	 for(int i = 0; i < NR_POINT_LIGHTS; i++)
	 {
		 outPutColor += CalcuPointLight(m_PointLights[i], norm, u_WorldPos, viewDir);
	 }
	 //����۹�
	 outPutColor +=CalcuSpotLight(m_SpolitLight, norm, u_WorldPos, viewDir);

	 color = vec4(outPutColor, 1.f);
}

vec3 CalcuDirLight(Light light, vec3 normal, vec3 viewdir)
{
	/*
	 * ƽ�й�
	*/
	//����������
	vec3 lightDir	= normalize(-light.direction);
	float diff		= max(dot(normal, lightDir), 0.f);
	vec3 diffuse	= diff * vec3(texture(m_Material.diffuse, u_TexCoord)) * light.diffuse;

	//����߹�
	//�۲��������ӱ���ָ���Դ��
	vec3 reflectDir		= reflect(-lightDir, normal);		//���䷨��
	float spec			= pow(max(dot(viewdir, reflectDir), 0.0), m_Material.shininess);
	vec3 specular		= vec3(texture(m_Material.specular, u_TexCoord)) * spec * light.specular;

	//���㻷����
	vec3 ambient	= vec3(texture(m_Material.diffuse, u_TexCoord)) * light.ambient;

	return (ambient + diffuse + specular);
}

vec3 CalcuPointLight(PointLight light, vec3 normal, vec3 point, vec3 viewdir)
{
	/*
	 * ���Դ
	*/
	//����������
	vec3 lightDir	= normalize(light.position - point);
	float diff		= max(dot(normal, lightDir), 0.f);
	vec3 diffuse	= diff * vec3(texture(m_Material.diffuse, u_TexCoord)) * light.diffuse;

	//���㻷����
	vec3 ambient		= vec3(texture(m_Material.diffuse, u_TexCoord)) * light.ambient;

	//����߹�
	//�۲��������ӱ���ָ���Դ��
	vec3 reflectDir		= reflect(-lightDir, normal);		//���䷨��
	float spec			= pow(max(dot(viewdir, reflectDir), 0.0), m_Material.shininess);
	vec3 specular		= vec3(texture(m_Material.specular, u_TexCoord)) * spec * light.specular;

	//�������˥��
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
	 * �۹�
	*/
	//���㻷����
	vec3 ambient = vec3(texture(m_Material.diffuse, u_TexCoord)) * light.ambient;

	//����������
	vec3 lightDir = normalize(-light.direction);
	float diff		= max(dot(normal, lightDir), 0.f);
	vec3 diffuse	= diff * vec3(texture(m_Material.diffuse, u_TexCoord)) * light.diffuse;

	//����߹�
	//�۲��������ӱ���ָ���Դ��
	vec3 reflectDir		= reflect(-lightDir, normal);		//���䷨��
	float spec			= pow(max(dot(viewdir, reflectDir), 0.0), m_Material.shininess);
	vec3 specular		= vec3(texture(m_Material.specular, u_TexCoord)) * spec * light.specular;

	//�������˥��
	float distance		= length(light.position - point);
	float attenuation	= 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
	ambient				*= attenuation;
	diffuse				*= attenuation;
	specular			*= attenuation;

	//�۹���ļ���
	//Ƭ��ָ���Դ������
	vec3 dir = normalize(light.position - point);
	//�Ƕ�
	float theta = dot(dir, normalize(-light.direction));
	//ƽ������
	float intensity = clamp((theta - light.outerCutOff) / (light.cutOff - light.outerCutOff), 0.f, 1.f);
	//���Ի���������Ӱ��
	//ambient		*= intensity;
	diffuse		*= intensity;
	specular	*= intensity;

	return (ambient + diffuse + specular);
}
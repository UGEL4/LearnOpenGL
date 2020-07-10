#version 460 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	//���淴��뾶
	float shininess;
};

in vec2 u_TexCoord;

uniform Material m_Material;

out vec4 color;

void main()
{
	color = texture(m_Material.diffuse, u_TexCoord);
}

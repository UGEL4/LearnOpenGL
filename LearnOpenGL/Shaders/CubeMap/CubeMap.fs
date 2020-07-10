#version 460 core

uniform samplerCube skyBox;

in vec3 u_TexCoord;

out vec4 color;

void main()
{
	color = texture(skyBox, u_TexCoord);
}

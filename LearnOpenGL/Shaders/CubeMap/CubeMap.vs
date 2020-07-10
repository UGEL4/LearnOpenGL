#version 460 core

layout(location = 0) in vec3 position;

uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 u_TexCoord;
void main()
{
	vec4 pos = projMat * viewMat * vec4(position, 1.f);
	gl_Position = pos.xyww;
	u_TexCoord = position;
}
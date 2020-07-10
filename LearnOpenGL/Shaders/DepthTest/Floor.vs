#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

layout(std140, binding = 2) uniform Matrices
{
	mat4 projMat;
	mat4 viewMat;
};
uniform mat4 modelMat;

out vec2 u_TexCoord;
void main()
{
	gl_Position = projMat * viewMat * modelMat  * position;
	u_TexCoord = texCoord;
}
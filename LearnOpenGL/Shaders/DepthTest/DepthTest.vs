#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

layout(std140, binding = 2) uniform Matrices
{
	mat4 projMat;
	mat4 viewMat;
};
uniform mat4 modelMat;

out vec3 u_Normal;
out vec3 u_WorldPos;
out vec2 u_TexCoord;

void main()
{
	gl_Position = projMat * viewMat * modelMat  * position ;

	u_TexCoord = texCoord;

	u_Normal = normal;
	u_WorldPos = vec3(modelMat * position);
}
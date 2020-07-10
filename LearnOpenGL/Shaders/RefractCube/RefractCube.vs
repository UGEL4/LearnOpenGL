#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout(std140, binding = 2) uniform Matrices
{
	mat4 projMat;
	mat4 viewMat;
};
uniform mat4 modelMat;

out vec3 u_FragWorldPos;
out vec3 u_Normal;
void main()
{
	gl_Position = projMat * viewMat * modelMat * vec4(position, 1.f);

	u_FragWorldPos = vec3(modelMat * vec4(position, 1.f));
	u_Normal = mat3(transpose(inverse(modelMat))) * normal;
}
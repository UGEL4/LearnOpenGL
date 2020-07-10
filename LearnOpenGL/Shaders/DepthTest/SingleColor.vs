#version 460 core

layout(location = 0) in vec4 position;

layout(std140, binding = 2) uniform Matrices
{
	mat4 projMat;
	mat4 viewMat;
};
uniform mat4 modelMat;

void main()
{
	gl_Position = projMat * viewMat * modelMat  * position ;
}
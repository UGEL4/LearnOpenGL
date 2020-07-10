#version 460 core

layout(location = 0) in vec4 position;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

uniform vec3 color;

out vec4 u_Color;

void main()
{
	
	gl_Position = projMat * viewMat * modelMat * position;

	u_Color = vec4(color, 1.f);
}
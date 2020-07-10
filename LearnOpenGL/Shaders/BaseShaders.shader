#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
uniform mat4 model_transform;
uniform mat4 view;
uniform mat4 projection;
out vec4 u_Color;
void main()
{
	gl_Position = position;
	u_Color = vec4(color, 1.f);
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;
in vec4 u_Color;
void main()
{
	color = u_Color;
}
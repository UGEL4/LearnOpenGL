#version 460 core

in vec3 u_FragWorldPos;
in vec3 u_Normal;

uniform samplerCube skyBox;
uniform vec3 cameraPos;
out vec4 color;

void main()
{
	float rate = 1.f / 1.52f;
	vec3 I = normalize(u_FragWorldPos - cameraPos);
	vec3 R = normalize(reflect(I, normalize(u_Normal)));

	color = vec4(texture(skyBox, R).rgb, 1.f);
}

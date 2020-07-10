#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitTangent;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform vec3 viewPos;
uniform vec3 lightPos;

out vec3 u_Normal;
out vec3 u_WorldPos;
out vec2 u_TexCoord;
out vec3 u_ViewPos;

out vec3 tangentLightPos;
out vec3 tangentViewPos;
out vec3 tangentFragPos;

void main()
{
	gl_Position = projMat * viewMat * modelMat * vec4(position,1.f);
	u_WorldPos = vec3(modelMat * vec4(position, 1.f));
	u_TexCoord = texCoord;
	u_ViewPos = viewPos;

	mat3 normalMatrix = transpose(inverse(mat3(modelMat)));
	vec3 T = normalize(normalMatrix * tangent);
    vec3 B = normalize(normalMatrix * bitTangent);
    vec3 N = normalize(normalMatrix * normal);
	//T = normalize(T - dot(T, N) * N);
	// then retrieve perpendicular vector B with the cross product of T and N
	//vec3 B = cross(T, N);

    mat3 TBN = transpose(mat3 (T,B,N));
	tangentLightPos = TBN * lightPos;
	tangentViewPos = TBN * viewPos;
	tangentFragPos = TBN * u_WorldPos;



	//u_Normal = normalMatrix * normal;
}
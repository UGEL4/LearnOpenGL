#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out VS_OUT {
    vec3 normal;
} vs_out;

uniform mat4 viewMat;
uniform mat4 modelMat;

void main()
{
    mat3 normalMatrix = mat3(transpose(inverse(viewMat * modelMat)));
    vs_out.normal = vec3(vec4(normalMatrix * aNormal, 0.0));
    gl_Position = viewMat * modelMat * vec4(aPos, 1.0); 
}
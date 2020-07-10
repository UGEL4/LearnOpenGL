#pragma once
#include <glm/glm.hpp>
#include <string>
class Light
{
public:
	Light(const std::string& VShaderFile, const std::string& FShaderFile, 
		glm::vec3 position = glm::vec3(0.f,0.f,0.f));
	~Light();

	void LoadShader(const std::string& vs, const std::string& fs);

private:
	glm::vec3 m_Position;
	class Shader* m_Shader;
	unsigned int m_Vao, m_Vbo, m_Ibo;
};


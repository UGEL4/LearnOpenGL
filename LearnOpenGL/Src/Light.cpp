#include "Light.h"
#include "Shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Light::Light(const std::string& VShaderFile, const std::string& FShaderFile, glm::vec3 position)
	:m_Position(position)
{
	LoadShader(VShaderFile, FShaderFile);

	//GLCALL(glGenVertexArrays(1, &m_Vao));
	//GLCALL(glBindVertexArray(m_Vao));

	//GLCALL(glGenBuffers(1, &m_Vbo));
	//GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_Vbo));
	//GLCALL(glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW));

	//GLCALL(glGenBuffers(1, &m_Ibo));
	//GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo));
	//GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW));
	////¶¥µã
	//GLCALL(glEnableVertexAttribArray(0));
	//GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0));

	////·¨Ïß
	////GLCALL(glEnableVertexAttribArray(1));
	////GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::m_Normal)));

	////ÌùÍ¼
	//GLCALL(glEnableVertexAttribArray(2));
	//GLCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::m_TexCoords)));

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//GLCALL(glBindVertexArray(0));
}

Light::~Light()
{
	delete m_Shader;
}

void Light::LoadShader(const std::string& vs, const std::string& fs)
{
	m_Shader = new Shader(vs, fs);
}

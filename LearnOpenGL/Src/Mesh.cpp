#include "Mesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "gl_inf.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures)
	:m_Vertices(vertices)
	,m_Indices(indices)
	,m_TexTures(textures)
{
	std::cout << "num1: " << m_Indices.size() << std::endl;
	GLCALL(glGenVertexArrays(1, &m_Vao));
	GLCALL(glBindVertexArray(m_Vao));

	GLCALL(glGenBuffers(1, &m_Vbo));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_Vbo));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW));

	GLCALL(glGenBuffers(1, &m_Ibo));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW));
	//¶¥µã
	GLCALL(glEnableVertexAttribArray(0));
	GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));

	//·¨Ïß
	GLCALL(glEnableVertexAttribArray(1));
	GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Normal)));

	//ÌùÍ¼
	GLCALL(glEnableVertexAttribArray(2));
	GLCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_TexCoords)));

	GLCALL(glEnableVertexAttribArray(3));
	GLCALL(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Tangent)));

	GLCALL(glEnableVertexAttribArray(4));
	GLCALL(glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Bitangent)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	GLCALL(glBindVertexArray(0));
}

Mesh::~Mesh()
{
	glBindVertexArray(0);
	std::vector<unsigned int>().swap(m_Indices);
	std::vector<Vertex>().swap(m_Vertices);
	for (auto t : m_TexTures)
	{
		delete t;
	}
	std::vector<Texture*>().swap(m_TexTures);
}

void Mesh::Draw(class Shader* shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < m_TexTures.size(); i++)
	{
		std::string number;
		std::string name = m_TexTures[i]->GetTextureType();

		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		else if (name == "texture_normal")
			number = std::to_string(normalNr++);
		else if (name == "texture_height")
			number = std::to_string(heightNr++);


		//shader->SetUniform1f(("m_Material." + name + number).c_str(), i);
		shader->SetUniform1i(("m_Material." + name + number).c_str(), i);
		/*glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_TexTures[i]->GetRendererID());*/
		//glBindTexture(GL_TEXTURE_2D, m_TexTures[i]->GetRendererID());
		m_TexTures[i]->Bind(i);
	}
	//glActiveTexture(0);
	GLCALL(glBindVertexArray(m_Vao));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
	//GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo));
	GLCALL(glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0));
	//GLCALL(glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size()));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	GLCALL(glBindVertexArray(0));
}

#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
struct Vertex
{
	glm::vec3 m_Position;
	glm::vec3 m_Normal;
	glm::vec2 m_TexCoords;
	glm::vec3 m_Tangent;
	glm::vec3 m_Bitangent;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures);
	~Mesh();

	void Draw(class Shader* shader);

	std::vector<Vertex> GetVertices() const { return m_Vertices; }
	std::vector<unsigned int> GetIndices() const { return m_Indices; }

	void PushTexture(Texture* t) { m_TexTures.push_back(t); }

private:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture*> m_TexTures;
	unsigned int m_Vao, m_Vbo, m_Ibo;
};
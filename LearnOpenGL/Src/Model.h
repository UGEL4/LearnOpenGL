#pragma once

#include <vector>
#include <assimp/material.h>
class Model
{
public:
	Model(const char* path);
	~Model();

	void Draw(class Shader* shader);

	void LoadMesh(const char* path);
	std::vector<class Mesh*> GetMeshs() const { return m_Meshs; }
	void AddMesh(std::vector<class Mesh*> Meshs) { m_Meshs = Meshs; }
private:
	void ProcessNode(struct aiNode* node, const struct aiScene* scene);
	class Mesh* ProcessMesh(struct aiMesh* mesh, const struct aiScene* scene);
	void LoadMaterialTexture(struct aiMaterial* material, aiTextureType type, const std::string& typeName, std::vector<class Texture*>& texArray);
	
private:
	std::vector<class Mesh*> m_Meshs;
	std::string m_Directory;
};


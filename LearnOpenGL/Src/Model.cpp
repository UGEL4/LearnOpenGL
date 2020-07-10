#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "Mesh.h"


Model::Model(const char* path)
{
	LoadMesh(path);
}

Model::~Model()
{
	for (auto mesh : m_Meshs)
	{
		delete mesh;
	}
	std::vector<Mesh*>().swap(m_Meshs);
}

void Model::Draw(class Shader* shader)
{
	for (auto& mesh : m_Meshs)
	{
		mesh->Draw(shader);
	}
}

void Model::LoadMesh(const char* path)
{
	//加载scene
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
	}

	std::string s(path);
	m_Directory = s.substr(0, s.find_last_of('/') + 1);

	std::cout << "model patch: " << m_Directory << std::endl;

	//处理节点
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshs.push_back(ProcessMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}

}

Mesh* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<class Texture*> textures;

	//处理顶点
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex v;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		v.m_Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		v.m_Normal = vector;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			v.m_TexCoords = vec;
		}
		else
		{
			glm::vec2 vec;
			vec.x = 0.f;
			vec.y = 0.f;
			v.m_TexCoords = vec;
		}

		
		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		v.m_Tangent = vector;

		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		v.m_Bitangent = vector;

		vertices.push_back(v);
	}

	
	//处理顶点索引
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	std::cout << "num2: " << indices.size() << std::endl;

	//处理材质
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture*> diffuseMaps;
		LoadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse", diffuseMaps);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture*> specularMaps;
		LoadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular", specularMaps);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		std::vector<Texture*> normalMaps;
		LoadMaterialTexture(material, aiTextureType_NORMALS, "texture_normal", normalMaps);
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

		std::vector<Texture*> heightMaps;
		LoadMaterialTexture(material, aiTextureType_HEIGHT, "texture_height", heightMaps);
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	}
	return new Mesh(vertices, indices, textures);
}

void Model::LoadMaterialTexture(struct aiMaterial* material, aiTextureType type, const std::string& typeName, std::vector<class Texture*>& texArray)
{
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString str;
		material->GetTexture(type, i, &str);
		Texture* texture = new Texture(m_Directory + str.C_Str(), typeName.c_str());
		texArray.push_back(texture);
		//std::cout << "path: " << str.C_Str() << std::endl;
	}
}

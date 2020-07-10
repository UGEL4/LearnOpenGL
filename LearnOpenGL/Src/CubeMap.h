#pragma once
#include <string>
#include <vector>
class CubeMap
{
public:
	CubeMap(const std::vector<std::string>& facePath, bool flipUV = false);
	~CubeMap();

	void Bind();
	void Unbind();

	unsigned int GetRendererID() const { return m_RendererID; }
private:
	unsigned int m_RendererID;
};


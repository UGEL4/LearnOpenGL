#pragma once
#include <string>
#define STB_IMAGE_IMPLEMENTATION

class Texture
{
public:
	Texture(const std::string& path, const char* texType, bool flipUV = false);
	~Texture();

	void Bind(unsigned int slot = 0);
	void Unbind();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline int GetChannles() const { return m_Channles; }
	unsigned int GetRendererID() const { return m_RendererID; }
	const char* GetTextureType() const { return m_TexType; }
private:
	//std::string m_Path;
	unsigned int m_RendererID;
	int m_Width;
	int m_Height;
	int m_Channles;
	unsigned char* m_TextureBuffer;
	char* m_TexType;
};
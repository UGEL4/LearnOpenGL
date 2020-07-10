#include "Texture.h"
#include "stb_image.h"
#include "gl_inf.h"

Texture::Texture(const std::string& path, const char* texType, bool flipUV)
	:m_RendererID(0)
	,m_Width(0), m_Height(0), m_Channles(0)
	,m_TextureBuffer(nullptr)
{
	unsigned int len = std::strlen(texType);
	m_TexType = new char[len + 1];
	strcpy_s(m_TexType, len + 1, texType);

	GLCALL(glGenTextures(1, &m_RendererID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	//GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//≤ªƒ‹”√GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	stbi_set_flip_vertically_on_load(flipUV);
	m_TextureBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channles, 0);
	if (m_TextureBuffer)
	{
		GLenum format;
		if (m_Channles == 1)
			format = GL_RED;
		else if (m_Channles == 3)
			format = GL_RGB;
		else if (m_Channles == 4)
			format = GL_RGBA;

		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_TextureBuffer));
		GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
		GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

		stbi_image_free(m_TextureBuffer);
	}
	else
	{
		std::cout << "load image failed" << '\n';
		stbi_image_free(m_TextureBuffer);
	}
}

Texture::~Texture()
{
	std::cout << "des" << std::endl;
	GLCALL(glDeleteTextures(1, &m_RendererID));
	delete m_TexType;
}

void Texture::Bind(unsigned int slot /*= 0*/)
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind()
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

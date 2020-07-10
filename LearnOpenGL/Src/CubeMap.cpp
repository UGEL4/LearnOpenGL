#include "CubeMap.h"
#include "stb_image.h"
#include "gl_inf.h"

CubeMap::CubeMap(const std::vector<std::string>& facePath, bool flipUV /*= false*/)
{
	GLCALL(glGenTextures(1, &m_RendererID));
	GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));

	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

	stbi_set_flip_vertically_on_load(flipUV);
	for (int i = 0; i < facePath.size(); i++)
	{
		int width, height, channles;
		unsigned char* TextureBuffer = stbi_load(facePath[i].c_str(), &width, &height, &channles, 0);
		if (TextureBuffer)
		{
			GLCALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureBuffer));
			GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

			stbi_image_free(TextureBuffer);
		}
		else
		{
			std::cout << "load cubmap failed" << '\n';
			stbi_image_free(TextureBuffer);
		}
	}
}

CubeMap::~CubeMap()
{
	GLCALL(glDeleteTextures(1, &m_RendererID));
}

void CubeMap::Bind()
{
	GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));
}

void CubeMap::Unbind()
{
	GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

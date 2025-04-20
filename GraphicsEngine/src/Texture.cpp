#include "pch.h"

#include "stb_image.h"

#include "Log.h"
#include "Texture.h"
#include "SafeGL.h"

namespace GraphicsEngine
{

	auto CreateTextureFromFile(const Path& path) -> ITexturePtr
	{
		return std::make_shared<Texture>(path);
	}

	Texture::Texture(const Path& path)
	{
		GL::GenTextures(1, &m_Texture);
		GL::BindTexture(GL_TEXTURE_2D, m_Texture);
		
		// Wrapping parameters
		GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Filtering parameters
		GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int x;
		int y;
		int channels;
		stbi_uc* pImage = stbi_load(path.string().c_str(), &x, &y, &channels, 0);
		if (!pImage)
		{
			GetLog()->Error(std::format("Failed to load texture: {}", path.string()));
			return;
		}

		GLint internalFormat = (channels == 1) ? GL_R8 :
			(channels == 2) ? GL_RG8 :
			(channels == 3) ? GL_RGB8 :
			GL_RGBA8;

		GLint format = (channels == 1) ? GL_RED :
			(channels == 2) ? GL_RG :
			(channels == 3) ? GL_RGB :
			GL_RGBA;

		GL::TexImage2D(GL_TEXTURE_2D, 0, internalFormat, x, y, 0, format, GL_UNSIGNED_BYTE, pImage);
		GL::GenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(pImage);
	}

	auto Texture::GetId() const -> GLuint
	{
		return m_Texture;
	}

}

#include "pch.h"

#include "stb_image.h"

#include "Log.h"
#include "Texture.h"
#include "SafeGL.h"

namespace GraphicsEngine
{

	auto CreateTextureFromFile(const String& textureName, const Path& path) -> ITexturePtr
	{
		return std::make_shared<Texture>(textureName, path);
	}

	Texture::Texture(const String& textureName, const Path& path)
		: m_Name(textureName)
	{
		GL::GenTextures(1, &m_Texture);
		GL::BindTexture(GL_TEXTURE_2D, m_Texture);
		
		// Wrapping parameters
		GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Filtering parameters
		GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true);

		int x;
		int y;
		int channels;
		stbi_uc* pImage = stbi_load(path.string().c_str(), &x, &y, &channels, 0);
		if (!pImage)
		{
			GetLog()->Error(std::format("Failed to load texture: {}", path.string()));
			return;
		}

		GLint internalFormat = GL_R8;
		GLint format = GL_RED;
		switch (channels)
		{
			case 2:
				internalFormat = GL_RG8;
				format = GL_RG;
				break;			
			case 3:
				internalFormat = GL_RGB8;
				format = GL_RGB;
				break;
			case 4:
				internalFormat = GL_RGBA8;
				format = GL_RGBA;
				break;
			default:
				break;
		}

		GL::TexImage2D(GL_TEXTURE_2D, 0, internalFormat, x, y, 0, format, GL_UNSIGNED_BYTE, pImage);
		GL::GenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(pImage);
	}

	auto Texture::GetId() const -> GLuint
	{
		return m_Texture;
	}

    auto Texture::GetName() const -> String
    {
        return m_Name;
    }

}

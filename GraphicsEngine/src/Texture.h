#pragma once

#include "ITexture.h"

namespace GraphicsEngine
{

	class Texture : public ITexture
	{
	public:
		/// @brief Create a texture
		/// @param textureName the name should be the same name as in the shader
		/// @param path the image file for this texture
		Texture(const String& textureName, const Path& path);
		~Texture() override = default;

		auto GetId() const -> GLuint;
		auto GetName() const -> String;

	private:
		GLuint m_Texture = 0;
		String m_Name;
	};

	auto CreateTextureFromFile(const String& textureName, const Path& path) -> ITexturePtr;

}

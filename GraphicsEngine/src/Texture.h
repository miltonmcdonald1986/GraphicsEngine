#pragma once

#include <filesystem>

#include "Types.h"
#include "ITexture.h"

namespace GraphicsEngine
{

	class Texture : public ITexture
	{
	public:
		/// @brief Create a texture
		/// @param textureName the name should be the same name as in the shader
		/// @param path the image file for this texture
		Texture(std::string_view textureName, const std::filesystem::path& path);
		~Texture() override = default;

		auto GetId() const -> GLuint;
		auto GetName() const -> std::string_view;

	private:
		GLuint m_Texture = 0;
		std::string m_Name;
	};

	auto CreateTextureFromFile(std::string_view textureName, const std::filesystem::path& path) -> ITexturePtr;

}

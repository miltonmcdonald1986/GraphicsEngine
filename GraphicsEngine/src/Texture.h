#pragma once

#include "ITexture.h"

namespace GraphicsEngine
{

	class Texture : public ITexture
	{
	public:
		Texture(const Path& path);
		~Texture() override = default;

		auto GetId() const -> GLuint;

	private:
		GLuint m_Texture = 0;
	};

	auto CreateTextureFromFile(const Path& path) -> ITexturePtr;

}

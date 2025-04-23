#pragma once

#include <memory>

namespace GraphicsEngine
{

	class ITexture
	{
	public:
		virtual ~ITexture() = default;
	};

	using ITexturePtr = std::shared_ptr<ITexture>;
	using ITextures = std::vector<ITexturePtr>;

}

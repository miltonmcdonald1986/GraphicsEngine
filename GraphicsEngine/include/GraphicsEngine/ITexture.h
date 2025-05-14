#pragma once

#include <memory>
#include <vector>

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

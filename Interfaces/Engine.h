#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <string>

#include "glad/glad.h"

#include "Color.h"
#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine
{

	class GRAPHICSENGINE_API Engine
	{
	public:

		Engine();
		~Engine();

		std::vector<std::string> GetLatestLogMessages() const;

		std::optional<Color> GetBackgroundColor();

		void SetBackgroundColor(const Color& color);

	private:

#pragma warning( push )
#pragma warning( disable : 4251 )

		struct Impl;
		std::unique_ptr<Impl> m_upImpl;

#pragma warning( pop )

	};

}

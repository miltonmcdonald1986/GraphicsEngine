#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <string>

#include "glad/glad.h"

#include "glm/vec3.hpp"

#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine
{

	class GRAPHICSENGINE_API Engine
	{
	public:

		Engine();
		~Engine();

		std::optional<GLuint> AddTriangle(const std::array<glm::vec3, 3>& vertices);

	private:

#pragma warning( push )
#pragma warning( disable : 4251 )

		struct Impl;
		std::unique_ptr<Impl> m_upImpl;

#pragma warning( pop )

	};

}

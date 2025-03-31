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

		//template<typename T, int NumComponents>
		//auto AttachBufferToVertexArrayObject(GLuint vao, const std::vector<glm::vec<NumComponents, T> >& data) const -> bool
		//{
		//	GLuint buffer;
		//	glGenBuffers(1, &buffer);
		//	if (GL::GetError(__FILE__, __func__, __LINE__) != GL::ErrorFlag::NoError)
		//		return std::nullopt;

		//	glBindBuffer(GL_ARRAY_BUFFER, buffer);
		//	if (GL::GetError(__FILE__, __func__, __LINE__) != GL::ErrorFlag::NoError)
		//		return std::nullopt;

		//	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
		//	if (GL::GetError(__FILE__, __func__, __LINE__) != GL::ErrorFlag::NoError)
		//		return std::nullopt;

		//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//	if (GL::GetError(__FILE__, __func__, __LINE__) != GL::ErrorFlag::NoError)
		//		return std::nullopt;

		//	glEnableVertexAttribArray(0);
		//	if (GL::GetError(__FILE__, __func__, __LINE__) != GL::ErrorFlag::NoError)
		//		return std::nullopt;
		//}

		//template<typename T>
		//auto DefineSingleAttributeVertexArray(const std::vector<T>& data) const -> std::optional<GLuint>
		//{
		//	auto logger = spdlog::get("Engine");

		//	GLuint array;
		//	glGenVertexArrays(1, &array);
		//	if (GL::GetError(__FILE__, __func__, __LINE__) != GL::ErrorFlag::NoError)
		//		return std::nullopt;

		//	glBindVertexArray(array);
		//	if (GL::GetError(__FILE__, __func__, __LINE__) != GL::ErrorFlag::NoError)
		//		return std::nullopt;

		//	if (!AttachBufferToVertexArrayObject(array, data))
		//		return std::nullopt;

		//	return array;
		//}

		std::optional<GLuint> AddTriangle(const std::array<glm::vec3, 3>& vertices);

	private:

#pragma warning( push )
#pragma warning( disable : 4251 )

		struct Impl;
		std::unique_ptr<Impl> m_upImpl;

#pragma warning( pop )

	};

}

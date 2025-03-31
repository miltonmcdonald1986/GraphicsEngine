#include "pch.h"
#include "GraphicsEngine/Engine.h"

#include <fstream>
#include <memory>
#include <stack>
#include <string>

#include "glad/glad.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/ringbuffer_sink.h"

#include "glm/mat3x3.hpp"

#include "GraphicsEngine/Buffer.h"
#include "GraphicsEngine/GL.h"

namespace GraphicsEngine
{

	struct Engine::Impl
	{

	};

	Engine::Engine()
		: m_upImpl(std::unique_ptr<Impl>(new Impl()))
	{
		std::vector<spdlog::sink_ptr> sinks;
		
		sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs\\GraphicsEngine.log", 1024*1024*5, 3));
		
		auto ringbuffer_sink = std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(128);
		sinks.push_back(ringbuffer_sink);

		auto logger = std::make_shared<spdlog::logger>("Engine", std::begin(sinks), std::end(sinks));
		logger->set_level(spdlog::level::debug);
		spdlog::register_logger(logger);
		
		gladLoadGL();
	}

	Engine::~Engine()
	{
	}

	std::optional<GLuint> Engine::AddTriangle(const std::array<glm::vec3, 3>& vertices)
	{
		auto logger = spdlog::get("Engine");

		std::vector<float> v = {
			vertices[0].x, vertices[0].y, vertices[0].z,
			vertices[1].x, vertices[1].y, vertices[1].z,
			vertices[2].x, vertices[2].y, vertices[2].z
		};

		glm::mat4 A;
		A[0] = glm::vec4(vertices[0], 1.f);
		A[1] = glm::vec4(vertices[1], 1.f);
		A[2] = glm::vec4(vertices[2], 1.f);
		A[3] = glm::vec4(1.f, 1.f, 1.f, 1.f);
		auto det = glm::determinant(A);

		glm::mat4 B;
		B[0] = glm::vec4(2.f, 2.f, 0.f, 1.f);
		B[1] = glm::vec4(2.f, 3.f, 0.f, 1.f);
		B[2] = glm::vec4(3.f, 2.f, 0.f, 1.f);
		B[3] = glm::vec4(1.f, 1.f, 1.f, 1.f);

		auto M = B*glm::inverse(A);

		// Local vertices for every triangle are (-0.5, -0.5, 0), (0.5, -0.5, 0), (0, 0.5, 0)
		// We build a local coordinate matrix out of these vertices.
		glm::mat4 localCoordinates;
		localCoordinates[0] = glm::vec4(-0.5f, -0.5f, 0.f, 1.f);
		localCoordinates[1] = glm::vec4( 0.5f, -0.5f, 0.f, 1.f);
		localCoordinates[2] = glm::vec4( 0.f,   0.5f, 0.f, 1.f);
		localCoordinates[3] = glm::vec4( 1.f,   1.f,  1.f, 1.f);

		auto model = M;

		auto newPositions = model * localCoordinates;

		//auto transformed = 
		
		GLuint vao;
		glGenVertexArrays(1, &vao);
		if (GL_ERROR())
			return std::nullopt;

		/*DataStore dataStore = 
		{
			.m_Target	= GL::BufferBindingTarget::Array,
			.m_NumBytes = static_cast<signed long long int>(v.size()*sizeof(float)),
			.m_pData	= v.data(),
			.m_Usage	= GL::DataUsagePattern::StaticDraw
		};*/

		//Buffer buffer(dataStore);

		GLuint buffer;
		glGenBuffers(1, &buffer);

		glBindVertexArray(vao);
		if (GL_ERROR())
			return std::nullopt;

		glBindBuffer(GL_ARRAY_BUFFER, buffer);

		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), v.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
		if (GL_ERROR())
			return std::nullopt;

		glEnableVertexAttribArray(0);
		if (GL_ERROR())
			return std::nullopt;

		return vao;
	}

}

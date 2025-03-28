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

		auto optVAO = GL::GenOneVertexArray();
		if (!optVAO)
			return std::nullopt;

		auto optBuffer = GL::GenOneBuffer();
		if (!optBuffer)
			return std::nullopt;

		if (!GL::BindVertexArray(*optVAO))
			return std::nullopt;

		if (!GL::BindArrayBuffer(*optBuffer))
			return std::nullopt;

		if (!GL::BufferFloatData(GL::BufferBindingTarget::Array, v, GL::DataUsagePattern::StaticDraw))
			return std::nullopt;

		if (!GL::VertexAttribPointer(0, GL::AttributeSize::Three, GL::DataType::Float, GL_FALSE, 3 * sizeof(float), 0))
			return std::nullopt;

		if (!GL::EnableVertexAttribArray(0))
			return std::nullopt;

		GL::UnbindArrayBuffer();
		GL::UnbindVertexArray();

		return *optVAO;
	}

}

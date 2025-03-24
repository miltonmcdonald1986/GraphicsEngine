#include "pch.h"
#include "Engine.h"

#include <fstream>
#include <memory>
#include <stack>
#include <string>

#include "glad/glad.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/ringbuffer_sink.h"

#include "GLUtilities.h"

namespace GraphicsEngine
{

	struct Engine::Impl
	{

		std::optional<Color> GetBackgroundColor()
		{
			float color[4];
			glGetFloatv(GL_COLOR_CLEAR_VALUE, color);

			GLenum error = glGetError();
			if (error == GL_INVALID_ENUM)
			{
				spdlog::get("Engine")->error("GL_COLOR_CLEAR_VALUE is not an accepted value.");
				return std::nullopt;
			}

			return Color(color);
		}

		void SetBackgroundColor(const Color& color)
		{
			glClearColor(color[0], color[1], color[2], color[3]);
		}
	};

	Engine::Engine()
		: m_upImpl(std::unique_ptr<Impl>(new Impl()))
	{
		auto ringbuffer_sink = std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(128);

		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("EngineLog.txt"));
		sinks.push_back(ringbuffer_sink);

		auto logger = std::make_shared<spdlog::logger>("Engine", std::begin(sinks), std::end(sinks));
		logger->set_level(spdlog::level::debug);
		spdlog::register_logger(logger);
		
		if (gladLoadGL() == 0)
			spdlog::get("Engine")->info("gladLoadGL failed.");
		else
			spdlog::get("Engine")->info("gladLoadGL succeeded.");
	}

	Engine::~Engine()
	{
	}

	std::optional<GLuint> Engine::AddTriangle(const std::array<glm::vec3, 3>& vertices)
	{
		using namespace GraphicsEngine::Utilities;

		auto logger = spdlog::get("Engine");

		std::vector<float> v = {
			vertices[0].x, vertices[0].y, vertices[0].z,
			vertices[1].x, vertices[1].y, vertices[1].z,
			vertices[2].x, vertices[2].y, vertices[2].z
		};

		auto optVAO = GenOneVertexArray();
		if (!optVAO)
		{
			logger->error("GenOneVertexArray return nullopt.");
			return std::nullopt;
		}

		auto optBuffer = GenOneBuffer();
		if (!optBuffer)
		{
			logger->error("GenOneBuffer returned nullopt.");
			return std::nullopt;
		}

		if (!BindVertexArray(*optVAO))
		{
			logger->error("BindVertexArray returned false.");
			return std::nullopt;
		}

		if (!BindArrayBuffer(*optBuffer))
		{
			logger->error("BindArrayBuffer returned false.");
			return std::nullopt;
		}

		if (!BufferFloatData(BufferBindingTarget::Array, v, DataUsagePattern::StaticDraw))
		{
			logger->error("BufferData returned false.");
			return std::nullopt;
		}

		if (!VertexAttribPointer(0, AttributeSize::Three, DataType::Float, GL_FALSE, 3 * sizeof(float), 0))
		{
			logger->error("VertexAttribPointer returned false.");
			return std::nullopt;
		}

		if (!EnableVertexAttribArray(0))
		{
			logger->error("EnableVertexAttribArray returned false.");
			return std::nullopt;
		}

		if (!UnbindArrayBuffer())
			logger->warn("UnbindArrayBuffer returned false.");

		if (!UnbindVertexArray())
			logger->warn("UnbindVertexArray returned false.");

		return *optVAO;
	}

	std::vector<std::string> Engine::GetLatestLogMessages() const
	{
		auto sinks = spdlog::get("Engine")->sinks();
		for (auto sink : sinks)
		{
			if (auto spRingbuffer = std::dynamic_pointer_cast<spdlog::sinks::ringbuffer_sink_mt>(sink))
				return spRingbuffer->last_formatted();
		}

		return {};
	}

	std::optional<Color> Engine::GetBackgroundColor()
	{
		return m_upImpl->GetBackgroundColor();
	}

	void Engine::SetBackgroundColor(const Color& color)
	{
		m_upImpl->SetBackgroundColor(color);
	}

}

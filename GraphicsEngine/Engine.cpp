#include "pch.h"
#include "Engine.h"

#include "GraphicsEngine/GL.h"
#include "GraphicsEngine/EntityType.h"

#include "Entity.h"

// VAO names
const std::string NamedVAOTriangleBasic = "Triangle Basic";
const std::string NamedVAOTriangleRGB = "Triangle RGB";

// Shader names
const std::string NamedShaderTriangleBasic = "Triangle Basic";
const std::string NamedShaderTriangleRGB = "Triangle RGB";

namespace
{

	auto BuildProgram(const std::map<GLenum, const char*>& shaderMap, GLuint program) -> bool
	{
		std::vector<GLuint> shaders;
		for (auto [shaderType, source] : shaderMap)
		{
			auto shader = GraphicsEngine::GL::CreateShader(shaderType);
			shaders.push_back(shader);

			std::vector<const GLchar*> strings;
			strings.push_back(source);

			GraphicsEngine::GL::ShaderSource(shader, static_cast<GLsizei>(strings.size()), strings.data(), nullptr);
			GraphicsEngine::GL::CompileShader(shader);

			int success;
			GraphicsEngine::GL::GetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				char infoLog[512];
				GraphicsEngine::GL::GetShaderInfoLog(shader, 512, NULL, infoLog);
				spdlog::get("Engine")->error(std::format("{}\t{}\t{}\t{}", std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, infoLog));
				return false;
			}
		}

		for (auto shader : shaders)
		{
			GraphicsEngine::GL::AttachShader(program, shader);
		}

		GraphicsEngine::GL::LinkProgram(program);
		bool success = GraphicsEngine::GL::GetLinkStatus(program);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			return false;
		}

		for (auto shader : shaders)
		{
			glDeleteShader(shader);
		}

		return true;
	}

	auto InitializeShaderTriangleBasic(GLuint program) -> bool
	{
		std::map<GLenum, const char*> shaderMap =
		{
			std::make_pair(GL_VERTEX_SHADER, "#version 330 core\n"
				"layout (location = 0) in vec3 aPos;\n"
				"void main()\n"
				"{\n"
				"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
				"}\0"),
			std::make_pair(GL_FRAGMENT_SHADER, "#version 330 core\n"
				"out vec4 FragColor;\n"
				"void main()\n"
				"{\n"
				"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
				"}\n\0")
		};

		return BuildProgram(shaderMap, program);
	}

	auto InitializeShaderTriangleRGB(GLuint program) -> bool
	{
		std::map<GLenum, const char*> shaderMap =
		{
			std::make_pair(GL_VERTEX_SHADER, "#version 330 core\n"
				"layout (location = 0) in vec3 aPos;\n"
				"layout(location = 1) in vec3 aColor;\n"

		        "out vec3 ourColor;\n"

		        "void main()\n"
		        "{\n"
				"   gl_Position = vec4(aPos, 1.0);\n"
				"   ourColor = aColor;\n"
				"}\0"),
			std::make_pair(GL_FRAGMENT_SHADER, "#version 330 core\n"
				"out vec4 FragColor;\n"

				"in vec3 ourColor;\n"

				"void main()\n"
				"{\n"
				"FragColor = vec4(ourColor.x, ourColor.y, ourColor.z, 1.0);\n"
				"}\0")
		};

		return BuildProgram(shaderMap, program);
	}

	auto InitializeVAOTriangleBasic(GLuint vao) -> bool
	{
		GraphicsEngine::GL::BindVertexArray(vao);

		GLuint buffer;
		glGenBuffers(1, &buffer);
		GraphicsEngine::GL::BindBuffer(GL_ARRAY_BUFFER, buffer);

		float vertices[] =
		{
			-0.5f, -0.5f, 0.f,
			 0.5f, -0.5f, 0.f,
			 0.f,   0.5f, 0.f
		};

		GraphicsEngine::GL::BufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		return true;
	}

	auto InitializeVAOTriangleRGB(GLuint vao) -> bool
	{
		float vertices[] =
		{
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		GraphicsEngine::GL::BindVertexArray(vao);

		GLuint buffer;
		glGenBuffers(1, &buffer);
		GraphicsEngine::GL::BindBuffer(GL_ARRAY_BUFFER, buffer);
		GraphicsEngine::GL::BufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Set up the positions

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		// Set up the colors

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);

		return true;
	}

}

namespace GraphicsEngine
{

	Engine::Engine()
	{
		InitializeLogging();
		InitializeOpenGL();
		InitializeVAOs();
		InitializeShaders();

		GL::ClearColor(0.f, 0.f, 0.f, 1.f);
		GL::ClearColorBuffer();
	}

	Engine::~Engine()
	{
		spdlog::drop_all();
	}

	auto Engine::GenerateEntity(EntityType type) -> unsigned int
	{
		Entity entity;
		entity.m_Type = type;
		entity.m_Id = NextAvailableEntityId();
		
		switch (type)
		{
		case GraphicsEngine::EntityType::TriangleBasic:
			entity.m_Shader = m_Shaders[NamedShaderTriangleBasic];
			entity.m_VAO = m_VAOs[NamedVAOTriangleBasic];
			break;
		case GraphicsEngine::EntityType::TriangleRGB:
			entity.m_Shader = m_Shaders[NamedShaderTriangleRGB];
			entity.m_VAO = m_VAOs[NamedVAOTriangleRGB];
			break;
		default:
			DebugBreak(); // We apparently need to support a new type.
			break;
		}

		m_Entities.insert(entity);

		return entity.m_Id;
	}

	auto Engine::Render() const -> void
	{
		GL::ClearColorBuffer();
		
		for (const auto& entity : m_Entities)
		{
			GL::UseProgram(entity.m_Shader);
			GL::BindVertexArray(entity.m_VAO);
			switch (entity.m_Type)
			{
			case GraphicsEngine::EntityType::TriangleBasic:
			case GraphicsEngine::EntityType::TriangleRGB:
				glDrawArrays(GL_TRIANGLES, 0, 3);
				break;
			default:
				DebugBreak(); // We apparently need to support a new type.
				break;
			}
		}
	}

	Engine::operator bool() const
	{
		return m_Initialized;
	}

	auto Engine::InitializeVAOs() -> bool
	{
		std::vector<GLuint> vaos(2);
		GL::GenVertexArrays(2, vaos.data());

		m_VAOs[NamedVAOTriangleBasic] = vaos[0];
		m_VAOs[NamedVAOTriangleRGB] = vaos[1];

		if (!InitializeVAOTriangleBasic(m_VAOs[NamedVAOTriangleBasic]))
			return false;

		if (!InitializeVAOTriangleRGB(m_VAOs[NamedVAOTriangleRGB]))
			return false;

		return true;
	}

	auto Engine::InitializeShaders() -> bool
	{
		m_Shaders[NamedShaderTriangleBasic] = GL::CreateProgram();
		m_Shaders[NamedShaderTriangleRGB] = GL::CreateProgram();
		
		if (!InitializeShaderTriangleBasic(m_Shaders[NamedShaderTriangleBasic]))
			return false;

		if (!InitializeShaderTriangleRGB(m_Shaders[NamedShaderTriangleRGB]))
			return false;

		return true;
	}

	auto Engine::InitializeLogging() -> bool
	{
		std::vector<spdlog::sink_ptr> sinks;

		// A rotating file sink provides logging that can be viewed in a text editor after the engine shuts down.

		auto spRotatingFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs\\GraphicsEngine.log", 1024 * 1024 * 5, 3);
		if (!spRotatingFileSink)
			return false;

		sinks.push_back(spRotatingFileSink);

		// A ringbuffer sink keeps 128 messages in memory to be accessed by any client of the engine during runtime.

		auto spRingbufferSink = std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(128);
		if (!spRingbufferSink)
			return false;

		sinks.push_back(spRingbufferSink);

		// Create a logger with our sinks.

		m_spLogger = std::make_shared<spdlog::logger>("Engine", std::begin(sinks), std::end(sinks));
		if (!m_spLogger)
			return false;

		m_spLogger->set_level(spdlog::level::debug);
		spdlog::register_logger(m_spLogger);

		return true;
	}

	auto Engine::InitializeOpenGL() -> bool
	{
		return (gladLoadGL() != 0);
	}

	auto Engine::NextAvailableEntityId() const -> unsigned int
	{
		unsigned int id = 1;

		auto EntityHasId = [&id](const Entity entity)
			{
				return entity.m_Id == id;
			};

		while (std::find_if(m_Entities.begin(), m_Entities.end(), EntityHasId) != m_Entities.end())
		{
			id++;
		}

		return id;
	}

	auto CreateEngine() -> IEngineSharedPtr
	{
		return IEngineSharedPtr(new Engine());
	}

}

#include "pch.h"
#include "Engine.h"

#include <array>

#include "IEngine.h"
#include "IShader.h"
#include "Entity.h"
#include "Error.h"
#include "SafeGL.h"
#include "Debug.h"

using namespace GraphicsEngine;

//// Shared VAO names
const std::string NamedVAOTriangleBasic = "Triangle Basic";
const std::string NamedVAOTriangleRGB = "Triangle RGB";

//// Shared Shader names
const std::string NamedShaderTriangleBasic = "Triangle Basic";
const std::string NamedShaderTriangleRGB = "Triangle RGB";

GEengine* geCreateGraphicsEngine()
{
	return new GEengine();
}

void geDestroyGraphicsEngine(GEengine* pEngine)
{
	delete pEngine;
}

unsigned int geGenerateEntity_IndexedPoints3DBasic(GEengine* pEngine, unsigned long long numVertexBytes, float* vertices, unsigned long long numIndexBytes, unsigned int* indices)
{
	return pEngine->GenerateEntity_IndexedPoints3DBasic(numVertexBytes, vertices, numIndexBytes, indices);
}

unsigned int geGenerateEntity_Triangle3DBasic(GEengine* pEngine)
{
	return pEngine->GenerateEntity_Triangle3DBasic();
}

unsigned int geGenerateEntity_Triangle3DRGB(GEengine* pEngine)
{
	return pEngine->GenerateEntity_Triangle3DRGB();
}

void geGetBackgroundColor(float color[4])
{
	GL::GetFloatv(GL_COLOR_CLEAR_VALUE, color);
}

GEshader* geGetCurrentShaderProgram(GEengine* pEngine)
{
	return pEngine->GetCurrentShaderProgram();
}

GElogLevel geGetLogLevel()
{
	//spdlog::level::level_enum level = spdlog::get("Engine")->level();
	//switch (level)
	//{
	//case spdlog::level::trace:
	//	return GE_LOG_LEVEL_TRACE;
	//case spdlog::level::debug:
	//	return GE_LOG_LEVEL_DEBUG;
	//case spdlog::level::info:
	//	return GE_LOG_LEVEL_INFO;
	//case spdlog::level::warn:
	//	return GE_LOG_LEVEL_WARN;
	//case spdlog::level::err:
	//	return GE_LOG_LEVEL_ERR;
	//case spdlog::level::critical:
	//	return GE_LOG_LEVEL_CRITICAL;
	//case spdlog::level::off:
	//	return GE_LOG_LEVEL_OFF;
	//}

	//DebugBreak(); // we really shouldn't get here.
	return GE_LOG_LEVEL_ERR;
}

GEpolygonMode geGetPolygonMode()
{
	std::vector<GLint> param(2);
	GL::GetIntegerv(GL_POLYGON_MODE, param.data());
	switch (param[0])
	{
	case GL_POINT:
		return GE_POLYGON_MODE_POINT;
	case GL_LINE:
		return GE_POLYGON_MODE_LINE;
	case GL_FILL:
	default:
		return GE_POLYGON_MODE_FILL;
	}
}

void geGetRecentLogMessages(GEengine* pEngine, int* numMessages, const char*** messages)
{
	pEngine->GetRecentLogMessages(numMessages, messages);
}

void geRender(GEengine* pEngine)
{
	pEngine->Render();
}

void geSetBackgroundColor(float color[4])
{
	GL::ClearColor(color[0], color[1], color[2], color[3]);
}

void geSetLogLevel(GElogLevel /*level*/)
{
	//auto logger = spdlog::get("Engine");
	//switch (level)
	//{
	//case GE_LOG_LEVEL_TRACE:
	//	logger->set_level(spdlog::level::level_enum::trace);
	//	break;
	//case GE_LOG_LEVEL_DEBUG:
	//	logger->set_level(spdlog::level::level_enum::debug);
	//	break;
	//case GE_LOG_LEVEL_INFO:
	//	logger->set_level(spdlog::level::level_enum::info);
	//	break;
	//case GE_LOG_LEVEL_WARN:
	//	logger->set_level(spdlog::level::level_enum::warn);
	//	break;
	//case GE_LOG_LEVEL_ERR:
	//	logger->set_level(spdlog::level::level_enum::err);
	//	break;
	//case GE_LOG_LEVEL_CRITICAL:
	//	logger->set_level(spdlog::level::level_enum::critical);
	//	break;
	//case GE_LOG_LEVEL_OFF:
	//	logger->set_level(spdlog::level::level_enum::off);
	//	break;
	//}
}

void geSetPolygonMode(GEpolygonMode mode)
{
	switch (mode)
	{
	case GE_POLYGON_MODE_POINT:
		GL::PolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case GE_POLYGON_MODE_LINE:
		GL::PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case GE_POLYGON_MODE_FILL:
	default:
		GL::PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
}

namespace
{

	auto BuildProgram(const std::map<GLenum, const char*>& shaderMap, GLuint program) -> bool
	{
		std::vector<GLuint> shaders;
		for (auto [shaderType, source] : shaderMap)
		{
			GLuint shader = GL::CreateShader(shaderType);
			shaders.push_back(shader);

			std::vector<const GLchar*> strings;
			strings.push_back(source);

			GL::ShaderSource(shader, static_cast<GLsizei>(strings.size()), strings.data(), nullptr);
			GL::CompileShader(shader);

			GLint success;
			GL::GetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				char infoLog[512];
				GL::GetShaderInfoLog(shader, 512, NULL, infoLog);
				//spdlog::get("Engine")->error(std::format("{}\t{}\t{}\t{}", std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, infoLog));
				return false;
			}
		}

		for (auto shader : shaders)
		{
			GL::AttachShader(program, shader);
		}

		GL::LinkProgram(program);
		GLint success;
		GL::GetProgramiv(program, GL_LINK_STATUS, &success);
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

	auto InitializeVAOTriangleBasic(GLuint vao) -> bool
	{
		GL::BindVertexArray(vao);

		GLuint buffer;
		GL::GenBuffers(1, &buffer);
		GL::BindBuffer(GL_ARRAY_BUFFER, buffer);

		float vertices[] =
		{
			-0.5f, -0.5f, 0.f,
			 0.5f, -0.5f, 0.f,
			 0.f,   0.5f, 0.f
		};

		GL::BufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

		GL::BindVertexArray(vao);

		GLuint buffer;
		glGenBuffers(1, &buffer);
		GL::BindBuffer(GL_ARRAY_BUFFER, buffer);
		GL::BufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Set up the positions

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		// Set up the colors

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		return true;
	}

}

GEengine::GEengine()
{
	//InitializeLogging();
	InitializeOpenGL();
	InitializeVAOs();
	InitializeShaders();

	GL::ClearColor(0.f, 0.f, 0.f, 1.f);
	GL::Clear(GL_COLOR_BUFFER_BIT);
}

GEengine::~GEengine()
{
	for (auto [_, pShader] : m_Shaders)
	{
		geDestroyShader(pShader);
	}

	//m_spLogger.reset();
}

void DrawIndexedPoints3DBasic(const Entity& entity)
{
	if (entity.m_Type != GE_ENTITY_TYPE_INDEXED_POINTS_BASIC)
		return;

	GL::UseProgram(entity.m_pShader->GetId());
	GL::BindVertexArray(entity.m_VAO);
	
	// Wrap this into safe gl handler.
	glDrawElements(GL_TRIANGLES, entity.m_NumIndices, GL_UNSIGNED_INT, (void*)0);
	HandleError(__FUNCTION__);
}

void DrawTriangle3DBasic(const Entity& entity)
{
	if (entity.m_Type != GE_ENTITY_TYPE_TRIANGLE_BASIC)
		return;

	GL::UseProgram(entity.m_pShader->GetId());
	GL::BindVertexArray(entity.m_VAO);
	GL::DrawArrays(GL_TRIANGLES, 0, 3);
}

void DrawTriangle3DRGB(const Entity& entity)
{
	if (entity.m_Type != GE_ENTITY_TYPE_TRIANGLE_RGB)
		return;

	GL::UseProgram(entity.m_pShader->GetId());
	GL::BindVertexArray(entity.m_VAO);
	GL::DrawArrays(GL_TRIANGLES, 0, 3);
}

auto CreateVAO_IndexedPoints3DBasic(unsigned long long vertexBytes, float* vertices, unsigned long long indexBytes, unsigned int* indices) -> GLuint
{
	GLuint vao;
	GL::GenVertexArrays(1, &vao);
	GL::BindVertexArray(vao);

	std::array<GLuint, 2> buffers;
	GL::GenBuffers(2, buffers.data());

	GL::BindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	GL::BufferData(GL_ARRAY_BUFFER, vertexBytes, vertices, GL_STATIC_DRAW);
	GL::VertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
	GL::EnableVertexAttribArray(0);

	GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	GL::BufferData(GL_ELEMENT_ARRAY_BUFFER, indexBytes, indices, GL_STATIC_DRAW);

	return vao;
}

auto GEengine::GenerateEntity_IndexedPoints3DBasic(unsigned long long numVertexBytes, float* vertices, unsigned long long numIndexBytes, unsigned int* indices) -> unsigned int
{
	Entity entity;
	entity.m_Type = GE_ENTITY_TYPE_INDEXED_POINTS_BASIC;
	entity.m_Id = NextAvailableEntityId();
	entity.m_pShader = m_Shaders[NamedShaderTriangleBasic];
	entity.m_VAO = CreateVAO_IndexedPoints3DBasic(numVertexBytes, vertices, numIndexBytes, indices);
	entity.m_NumIndices = static_cast<int>(numIndexBytes / sizeof(unsigned int));
	m_Entities.insert(entity);
	return entity.m_Id;
}

auto GEengine::GenerateEntity_Triangle3DBasic() -> unsigned int
{
	Entity entity;
	entity.m_Type = GE_ENTITY_TYPE_TRIANGLE_BASIC;
	entity.m_Id = NextAvailableEntityId();
	entity.m_pShader = m_Shaders[NamedShaderTriangleBasic];
	entity.m_VAO = m_VAOs[NamedVAOTriangleBasic];
	m_Entities.insert(entity);
	return entity.m_Id;
}

auto GEengine::GenerateEntity_Triangle3DRGB() -> unsigned int
{
	Entity entity;
	entity.m_Type = GE_ENTITY_TYPE_TRIANGLE_RGB;
	entity.m_Id = NextAvailableEntityId();
	entity.m_pShader = m_Shaders[NamedShaderTriangleRGB];
	entity.m_VAO = m_VAOs[NamedVAOTriangleRGB];
	m_Entities.insert(entity);
	return entity.m_Id;
}

auto GEengine::GetCurrentShaderProgram() -> GEshader*
{
	GLint prog;
	GL::GetIntegerv(GL_CURRENT_PROGRAM, &prog);
	auto it = std::find_if(m_Shaders.begin(), m_Shaders.end(), [&prog](const std::pair<std::string, GEshader*>& nameAndShader) 
		{
			return static_cast<int>(nameAndShader.second->GetId()) == prog;
		});

	if (it == m_Shaders.end())
		return 0;
	else
		return it->second;
}

auto GEengine::GetRecentLogMessages(int* /*numMessages*/, const char*** /*messages*/) -> void
{
	//auto sinks = spdlog::get("Engine")->sinks();
	//for (auto sink : sinks)
	//{
	//	if (auto spRingbuffer = std::dynamic_pointer_cast<spdlog::sinks::ringbuffer_sink_mt>(sink))
	//	{
	//		if (!m_LogMessages.empty())
	//		{
	//			for (auto& pStr : m_LogMessages)
	//			{
	//				delete[] pStr;
	//			}

	//			m_LogMessages.clear();
	//		}

	//		auto strings = spRingbuffer->last_formatted();
	//		*numMessages = strings.size();
	//		for (int i = 0; i < strings.size(); ++i)
	//		{
	//			auto sizeOfString = strings[i].size();
	//			char* newString = new char[sizeOfString + 1];
	//			std::fill(newString, newString + sizeOfString + 1, '\0');
	//			std::copy(strings[i].begin(), strings[i].end(), newString);
	//			m_LogMessages.push_back(newString);
	//		}
	//		
	//		if (!m_LogMessages.empty())
	//			*messages = m_LogMessages.data();
	//	}
	//}
}

auto GEengine::Render() const -> void
{
	GL::Clear(GL_COLOR_BUFFER_BIT);
	for (const auto& entity : m_Entities)
	{
		switch (entity.m_Type)
		{
		case GE_ENTITY_TYPE_INDEXED_POINTS_BASIC:
			DrawIndexedPoints3DBasic(entity);
			break;
		case GE_ENTITY_TYPE_TRIANGLE_BASIC:
			DrawTriangle3DBasic(entity);
			break;
		case GE_ENTITY_TYPE_TRIANGLE_RGB:
			DrawTriangle3DRGB(entity);
			break;
		default:
			BREAKPOINT; // We apparently need to support a new type.
			break;
		}
	}
}

auto GEengine::InitializeVAOs() -> bool
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

auto GEengine::InitializeShaderTriangleBasic() -> bool
{
	const std::string vertexShader = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}";

	const std::string fragmentShader = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}";

	auto pShader = geCreateShaderFromStrings(vertexShader.c_str(), nullptr, fragmentShader.c_str());
	if (!pShader)
		return false;

	m_Shaders.insert(std::make_pair(NamedShaderTriangleBasic, pShader));
	return true;
}

auto GEengine::InitializeShaderTriangleRGB() -> bool
{
	const std::string vertexShader = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aColor;\n"

		"out vec3 ourColor;\n"

		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"   ourColor = aColor;\n"
		"}";

	const std::string fragmentShader = "#version 330 core\n"
		"out vec4 FragColor;\n"

		"in vec3 ourColor;\n"

		"void main()\n"
		"{\n"
		"FragColor = vec4(ourColor.x, ourColor.y, ourColor.z, 1.0);\n"
		"}";

	auto pShader = geCreateShaderFromStrings(vertexShader.c_str(), nullptr, fragmentShader.c_str());
	if (!pShader)
		return false;

	m_Shaders.insert(std::make_pair(NamedShaderTriangleRGB, pShader));
	return true;
}

auto GEengine::InitializeShaders() -> bool
{
	if (!InitializeShaderTriangleBasic())
		return false;

	if (!InitializeShaderTriangleRGB())
		return false;

	return true;
}

auto GEengine::InitializeLogging() -> bool
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

	auto spLogger = std::make_shared<spdlog::logger>("Engine", std::begin(sinks), std::end(sinks));
	if (!spLogger)
		return false;

	spdlog::register_logger(spLogger);
	spLogger->set_level(spdlog::level::debug);

	return true;
}

auto GEengine::InitializeOpenGL() -> bool
{
	return (gladLoadGL() != 0);
}

auto GEengine::NextAvailableEntityId() const -> unsigned int
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

#include "pch.h"
#include "Engine.h"

#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/GL.h"
#include "GraphicsEngine/EntityType.h"

#include "Entity.h"
#include "Error.h"
#include "SafeGL.h"

using namespace GraphicsEngine;

// Shared VAO names
const std::string NamedVAOTriangleBasic = "Triangle Basic";
const std::string NamedVAOTriangleRGB = "Triangle RGB";

// Shared Shader names
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

unsigned int geGenerateEntity_IndexedPoints3DBasic(GEengine* pEngine, ByteCount vertexBytes, float* vertices, ByteCount indexBytes, Index* indices)
{
	return pEngine->GenerateEntity_IndexedPoints3DBasic(vertexBytes, vertices, indexBytes, indices);
}

unsigned int geGenerateEntity_Triangle3DBasic(GEengine* pEngine)
{
	return pEngine->GenerateEntity_Triangle3DBasic();
}

unsigned int geGenerateEntity_Triangle3DRGB(GEengine* pEngine)
{
	return pEngine->GenerateEntity_Triangle3DRGB();
}

void geRender(GEengine* pEngine)
{
	pEngine->Render();
}

int geSetVertices(GEengine* pEngine, unsigned int entId, unsigned long long size, float* data)
{
	return pEngine->SetVertices(entId, size, data);
}

namespace
{

	auto BuildProgram(const std::map<GLenum, const char*>& shaderMap, GLuint program) -> bool
	{
		std::vector<GLuint> shaders;
		for (auto [shaderType, source] : shaderMap)
		{
			GLuint shader = 0;
			switch (shaderType)
			{
			case GL_FRAGMENT_SHADER:
				shader = GL::CreateFragmentShader();
				break;
			case GL_GEOMETRY_SHADER:
				shader = GL::CreateGeometryShader();
				break;
			case GL_VERTEX_SHADER:
				shader = GL::CreateVertexShader();
				break;
			}

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
				spdlog::get("Engine")->error(std::format("{}\t{}\t{}\t{}", std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, infoLog));
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

		GL::ArrayBufferDataStaticDraw(sizeof(vertices), vertices);

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
		GL::ArrayBufferDataStaticDraw(sizeof(vertices), vertices);

		// Set up the positions

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		// Set up the colors

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		return true;
	}

}

//namespace GraphicsEngine
//{

GEengine::GEengine()
{
	InitializeLogging();
	InitializeOpenGL();
	InitializeVAOs();
	InitializeShaders();

	GL::ClearColor(0.f, 0.f, 0.f, 1.f);
	GL::ClearColorBuffer();
}

GEengine::~GEengine()
{
	spdlog::drop_all();
}

void DrawIndexedPoints3DBasic(const Entity& entity)
{
	if (entity.m_Type != GE_ENTITY_TYPE_INDEXED_POINTS_BASIC)
		return;

	GL::UseProgram(entity.m_Shader);
	GL::BindVertexArray(entity.m_VAO);
	
	// Wrap this into safe gl handler.
	glDrawElements(GL_TRIANGLES, entity.m_NumIndices, GL_UNSIGNED_INT, (void*)0);
	HandleError(__FUNCTION__);
}

void DrawTriangle3DBasic(const Entity& entity)
{
	if (entity.m_Type != GE_ENTITY_TYPE_TRIANGLE_BASIC)
		return;

	GL::UseProgram(entity.m_Shader);
	GL::BindVertexArray(entity.m_VAO);
	GL::DrawArraysAsTriangles(0, 3);
}

void DrawTriangle3DRGB(const Entity& entity)
{
	if (entity.m_Type != GE_ENTITY_TYPE_TRIANGLE_RGB)
		return;

	GL::UseProgram(entity.m_Shader);
	GL::BindVertexArray(entity.m_VAO);
	GL::DrawArraysAsTriangles(0, 3);
}

auto CreateVAO_IndexedPoints3DBasic(ByteCount vertexBytes, float* vertices, ByteCount indexBytes, Index* indices) -> GLuint
{
	GLuint vao;
	GL::GenVertexArrays(1, &vao);
	GL::BindVertexArray(vao);

	std::array<GLuint, 2> buffers;
	GL::GenBuffers(2, buffers.data());

	GL::BindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	GL::ArrayBufferDataStaticDraw(vertexBytes, vertices);
	GL::VertexAttribFloatPointer(0, 3, false, 3 * sizeof(float), (void*)0);
	GL::EnableVertexAttribArray(0);

	GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	GL::ElementArrayBufferDataStaticDraw(indexBytes, indices);

	return vao;
}

auto GEengine::GenerateEntity_IndexedPoints3DBasic(ByteCount vertexBytes, float* vertices, ByteCount indexBytes, Index* indices) -> unsigned int
{
	Entity entity;
	entity.m_Type = GE_ENTITY_TYPE_INDEXED_POINTS_BASIC;
	entity.m_Id = NextAvailableEntityId();
	entity.m_Shader = m_Shaders[NamedShaderTriangleBasic];
	entity.m_VAO = CreateVAO_IndexedPoints3DBasic(vertexBytes, vertices, indexBytes, indices);
	entity.m_NumIndices = static_cast<int>(indexBytes / sizeof(Index));
	m_Entities.insert(entity);
	return entity.m_Id;
}

auto GEengine::GenerateEntity_Triangle3DBasic() -> unsigned int
{
	Entity entity;
	entity.m_Type = GE_ENTITY_TYPE_TRIANGLE_BASIC;
	entity.m_Id = NextAvailableEntityId();
	entity.m_Shader = m_Shaders[NamedShaderTriangleBasic];
	entity.m_VAO = m_VAOs[NamedVAOTriangleBasic];
	m_Entities.insert(entity);
	return entity.m_Id;
}

auto GEengine::GenerateEntity_Triangle3DRGB() -> unsigned int
{
	Entity entity;
	entity.m_Type = GE_ENTITY_TYPE_TRIANGLE_RGB;
	entity.m_Id = NextAvailableEntityId();
	entity.m_Shader = m_Shaders[NamedShaderTriangleRGB];
	entity.m_VAO = m_VAOs[NamedVAOTriangleRGB];
	m_Entities.insert(entity);
	return entity.m_Id;
}

auto GEengine::Render() const -> void
{
	GL::ClearColorBuffer();

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
			DebugBreak(); // We apparently need to support a new type.
			break;
		}
	}
}

GEengine::operator bool() const
{
	return m_Initialized;
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

auto GEengine::InitializeShaders() -> bool
{
	m_Shaders[NamedShaderTriangleBasic] = GL::CreateProgram();
	m_Shaders[NamedShaderTriangleRGB] = GL::CreateProgram();

	if (!InitializeShaderTriangleBasic(m_Shaders[NamedShaderTriangleBasic]))
		return false;

	if (!InitializeShaderTriangleRGB(m_Shaders[NamedShaderTriangleRGB]))
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

	m_spLogger = std::make_shared<spdlog::logger>("Engine", std::begin(sinks), std::end(sinks));
	if (!m_spLogger)
		return false;

	m_spLogger->set_level(spdlog::level::debug);
	spdlog::register_logger(m_spLogger);

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

auto GEengine::SetVertices(unsigned int entId, unsigned long long size, float* data) -> bool
{
	if (auto entity = std::find_if(m_Entities.begin(), m_Entities.end(), [&entId](const Entity& entity) { return entity.m_Id == entId; }); entity != m_Entities.end())
	{
		switch (entity->m_Type)
		{
		case GE_ENTITY_TYPE_INDEXED_POINTS_BASIC:
		{
			// WHAT TO DO???
			break;
		}
		case GE_ENTITY_TYPE_TRIANGLE_BASIC:
			DebugBreak(); // Not implemented yet.
			break;
		case GE_ENTITY_TYPE_TRIANGLE_RGB:
			DebugBreak(); // Not implemented yet.
			break;
		}
	}
	return false;
}

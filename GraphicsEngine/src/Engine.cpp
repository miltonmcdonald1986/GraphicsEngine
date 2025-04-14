#include "pch.h"
#include "Engine.h"

#include "Debug.h"
#include "SafeGL.h"
#include "IShader.h"

namespace GraphicsEngine
{

	Engine::Engine()
	{

		if (gladLoadGL() == 0)
			BREAKPOINT;

		GL::ClearColor(0.f, 0.f, 0.f, 1.f);
		GL::Clear(GL_COLOR_BUFFER_BIT);
	}

	auto Engine::CreateNewShaderFromFiles(const std::filesystem::path& vert, const std::filesystem::path& geom, const std::filesystem::path& frag) -> IShaderPtr
	{
		auto GetSourceFromFile = [](const std::filesystem::path& path) -> std::string
		{
			if (path.empty())
				return "";

			if (!std::filesystem::exists(path))
			{
				auto cwd = std::filesystem::current_path();
				BREAKPOINT; // Trying to open a file that doesn't exist.
				return "";
			}

			std::ifstream ifs(path);
			std::stringstream buffer;
			buffer << ifs.rdbuf();

			std::string str(buffer.str());
			return str;
		};

		auto vertSource = GetSourceFromFile(vert);
		auto geomSource = GetSourceFromFile(geom);
		auto fragSource = GetSourceFromFile(frag);
		return CreateNewShaderFromSource(vertSource, geomSource, fragSource);
	}

	auto Engine::CreateNewShaderFromSource(const std::string& vert, const std::string& geom, const std::string& frag) -> IShaderPtr
	{
		return CreateShaderFromSourceCode(vert, geom, frag);
	}

	auto Engine::GetBackgroundColor() const -> Color
	{
		return m_BackgroundColor;
	}

	auto Engine::GetCurrentShader() const -> IShaderPtr
	{
		GLint id;
		GL::GetIntegerv(GL_CURRENT_PROGRAM, &id);
		auto it = std::find_if(m_Shaders.begin(), m_Shaders.end(), [&id](IShaderPtr spShader) 
			{
				return spShader->GetId() == id;
			});

		if (it == m_Shaders.end())
			return nullptr;

		return *it;
	}

	auto Engine::GetPolygonMode() const -> PolygonMode
	{
		return m_PolygonMode;
	}

	auto Engine::Render() const -> void
	{
		GL::Clear(GL_COLOR_BUFFER_BIT);
//	for (auto spEntity : m_Entities)
//	{
//		switch (spEntity->m_Type)
//		{
//		case GE_ENTITY_TYPE_INDEXED_POINTS_BASIC:
//			DrawIndexedPoints3DBasic(*spEntity);
//			break;
//		case GE_ENTITY_TYPE_POS3F:
//		case GE_ENTITY_TYPE_POS3F_COL3F:
//			GL::UseProgram(spEntity->m_pShader->GetId());
//			GL::BindVertexArray(spEntity->m_VAO);
//			GL::DrawArrays(GL_TRIANGLES, 0, spEntity->m_NumVertices);
//			break;
//		default:
//			BREAKPOINT; // We apparently need to support a new type.
//			break;
//		}
//	}
	}

	auto Engine::SetBackgroundColor(const Color& color) -> void
	{
		m_BackgroundColor = color;
		GL::ClearColor(m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b, m_BackgroundColor.a);
	}

	auto Engine::SetPolygonMode(PolygonMode polygonMode) -> void
	{
		m_PolygonMode = polygonMode;
		switch (m_PolygonMode)
		{
		case GraphicsEngine::PolygonMode::Fill:
			GL::PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case GraphicsEngine::PolygonMode::Line:
			GL::PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case GraphicsEngine::PolygonMode::Point:
			GL::PolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		}
	}

}

//
//#include <array>
//
//#include "IEngine.h"
//#include "IShader.h"
//#include "Entity.h"
//#include "Error.h"
//#include "SafeGL.h"
//#include "Debug.h"
//
//using namespace GraphicsEngine;
//
////// Shared Shader names
//const std::string NamedShaderTriangleBasic = "Triangle Basic";
//const std::string NamedShaderTriangleRGB = "Triangle RGB";
//
//namespace
//{
//
//	auto CreateVAO_Pos3f(unsigned long long numBytes, float* data) -> GLuint
//	{
//		GLuint vao;
//		GL::GenVertexArrays(1, &vao);
//		GL::BindVertexArray(vao);
//
//		GLuint buffer;
//		GL::GenBuffers(1, &buffer);
//		GL::BindBuffer(GL_ARRAY_BUFFER, buffer);
//		GL::BufferData(GL_ARRAY_BUFFER, numBytes, data, GL_STATIC_DRAW);
//
//		GL::VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//		GL::EnableVertexAttribArray(0);
//
//		return vao;
//	}
//
//	auto CreateVAO_Pos3fCol3f(unsigned long long numBytes, float* data) -> GLuint
//	{
//		GLuint vao;
//		GL::GenVertexArrays(1, &vao);
//		GL::BindVertexArray(vao);
//
//		GLuint buffers[2];
//		GL::GenBuffers(2, buffers);
//
//		GL::BindBuffer(GL_ARRAY_BUFFER, buffers[0]);
//		GL::BufferData(GL_ARRAY_BUFFER, numBytes, data, GL_STATIC_DRAW);
//		GL::VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
//		GL::EnableVertexAttribArray(0);
//
//		GL::BindBuffer(GL_ARRAY_BUFFER, buffers[1]);
//		GL::BufferData(GL_ARRAY_BUFFER, numBytes, data, GL_STATIC_DRAW);
//		GL::VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
//		GL::EnableVertexAttribArray(1);
//
//		return vao;
//	}
//
//}
//
////GEengine* geCreateGraphicsEngine()
////{
////	return new GEengine();
////}
////
////void geDestroyGraphicsEngine(GEengine* pEngine)
////{
////	delete pEngine;
////}
//
////unsigned int geGenerateEntity_IndexedPoints3DBasic(GEengine* pEngine, unsigned long long numVertexBytes, float* vertices, unsigned long long numIndexBytes, unsigned int* indices)
////{
////	return pEngine->GenerateEntity_IndexedPoints3DBasic(numVertexBytes, vertices, numIndexBytes, indices);
////}
//
////unsigned int geGenerateEntity_Pos3f(GEengine* pEngine, unsigned long long numBytes, float* data)
////{
////	auto spEntity = pEngine->AddEntity();
////	/*spEntity->m_Type = GE_ENTITY_TYPE_POS3F;
////	spEntity->m_pShader = pEngine->GetShader(NamedShaderTriangleBasic);
////	spEntity->m_VAO = CreateVAO_Pos3f(numBytes, data);
////	spEntity->m_NumIndices = 0;
////	spEntity->m_NumVertices = static_cast<unsigned int>(numBytes / (3*sizeof(float)));*/
////	return spEntity->m_Id;
////}
//
////unsigned int geGenerateEntity_Pos3fCol3f(GEengine* pEngine, unsigned long long numBytes, float* data)
////{
////	auto spEntity = pEngine->AddEntity();
////	//spEntity->m_Type = GE_ENTITY_TYPE_POS3F_COL3F;
////	//spEntity->m_pShader = pEngine->GetShader(NamedShaderTriangleRGB);
////	//spEntity->m_VAO = CreateVAO_Pos3fCol3f(numBytes, data);
////	//spEntity->m_NumIndices = 0;
////	//spEntity->m_NumVertices = static_cast<unsigned int>(numBytes / (6 * sizeof(float)));
////	return spEntity->m_Id;
////}
//
////void geGetBackgroundColor(float color[4])
////{
////	GL::GetFloatv(GL_COLOR_CLEAR_VALUE, color);
////}
////
////GEshader* geGetCurrentShaderProgram(GEengine* pEngine)
////{
////	return pEngine->GetCurrentShaderProgram();
////}
//
////GElogLevel geGetLogLevel()
////{
//	//spdlog::level::level_enum level = spdlog::get("Engine")->level();
//	//switch (level)
//	//{
//	//case spdlog::level::trace:
//	//	return GE_LOG_LEVEL_TRACE;
//	//case spdlog::level::debug:
//	//	return GE_LOG_LEVEL_DEBUG;
//	//case spdlog::level::info:
//	//	return GE_LOG_LEVEL_INFO;
//	//case spdlog::level::warn:
//	//	return GE_LOG_LEVEL_WARN;
//	//case spdlog::level::err:
//	//	return GE_LOG_LEVEL_ERR;
//	//case spdlog::level::critical:
//	//	return GE_LOG_LEVEL_CRITICAL;
//	//case spdlog::level::off:
//	//	return GE_LOG_LEVEL_OFF;
//	//}
//
//	//DebugBreak(); // we really shouldn't get here.
////	return GE_LOG_LEVEL_ERR;
////}
//
////void geGetRecentLogMessages(GEengine* pEngine, int* numMessages, const char*** messages)
////{
////	pEngine->GetRecentLogMessages(numMessages, messages);
////}
//
////void geRender(GEengine* pEngine)
////{
////	pEngine->Render();
////}
//
//void geSetBackgroundColor(float color[4])
//{
//	GL::ClearColor(color[0], color[1], color[2], color[3]);
//}
//
////void geSetEntityShader(GEengine* pEngine, unsigned int entId, GEshader* pShader)
////{
////	pEngine->SetEntityShader(entId, pShader);
////}
//
////void geSetLogLevel(GElogLevel /*level*/)
////{
//	//auto logger = spdlog::get("Engine");
//	//switch (level)
//	//{
//	//case GE_LOG_LEVEL_TRACE:
//	//	logger->set_level(spdlog::level::level_enum::trace);
//	//	break;
//	//case GE_LOG_LEVEL_DEBUG:
//	//	logger->set_level(spdlog::level::level_enum::debug);
//	//	break;
//	//case GE_LOG_LEVEL_INFO:
//	//	logger->set_level(spdlog::level::level_enum::info);
//	//	break;
//	//case GE_LOG_LEVEL_WARN:
//	//	logger->set_level(spdlog::level::level_enum::warn);
//	//	break;
//	//case GE_LOG_LEVEL_ERR:
//	//	logger->set_level(spdlog::level::level_enum::err);
//	//	break;
//	//case GE_LOG_LEVEL_CRITICAL:
//	//	logger->set_level(spdlog::level::level_enum::critical);
//	//	break;
//	//case GE_LOG_LEVEL_OFF:
//	//	logger->set_level(spdlog::level::level_enum::off);
//	//	break;
//	//}
////}
//
////void geSetPolygonMode(GEpolygonMode mode)
////{
////	switch (mode)
////	{
////	case GE_POLYGON_MODE_POINT:
////		GL::PolygonMode(GL_FRONT_AND_BACK, GL_POINT);
////		break;
////	case GE_POLYGON_MODE_LINE:
////		GL::PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
////		break;
////	case GE_POLYGON_MODE_FILL:
////	default:
////		GL::PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
////		break;
////	}
////}
//
//namespace
//{
//
//	auto BuildProgram(const std::map<GLenum, const char*>& shaderMap, GLuint program) -> bool
//	{
//		std::vector<GLuint> shaders;
//		for (auto [shaderType, source] : shaderMap)
//		{
//			GLuint shader = GL::CreateShader(shaderType);
//			shaders.push_back(shader);
//
//			std::vector<const GLchar*> strings;
//			strings.push_back(source);
//
//			GL::ShaderSource(shader, static_cast<GLsizei>(strings.size()), strings.data(), nullptr);
//			GL::CompileShader(shader);
//
//			GLint success;
//			GL::GetShaderiv(shader, GL_COMPILE_STATUS, &success);
//			if (!success)
//			{
//				char infoLog[512];
//				GL::GetShaderInfoLog(shader, 512, NULL, infoLog);
//				//spdlog::get("Engine")->error(std::format("{}\t{}\t{}\t{}", std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, infoLog));
//				return false;
//			}
//		}
//
//		for (auto shader : shaders)
//		{
//			GL::AttachShader(program, shader);
//		}
//
//		GL::LinkProgram(program);
//		GLint success;
//		GL::GetProgramiv(program, GL_LINK_STATUS, &success);
//		if (!success)
//		{
//			char infoLog[512];
//			glGetProgramInfoLog(program, 512, NULL, infoLog);
//			return false;
//		}
//
//		for (auto shader : shaders)
//		{
//			glDeleteShader(shader);
//		}
//
//		return true;
//	}
//
//}
//
//GEengine::GEengine()
//{
//	//InitializeLogging();
//	InitializeOpenGL();
//	InitializeShaders();
//
//	GL::ClearColor(0.f, 0.f, 0.f, 1.f);
//	GL::Clear(GL_COLOR_BUFFER_BIT);
//}
//
//GEengine::~GEengine()
//{
//	for (auto [_, pShader] : m_Shaders)
//	{
//		geDestroyShader(pShader);
//	}
//
//	//m_spLogger.reset();
//}
//
//void DrawIndexedPoints3DBasic(const Entity& entity)
//{
//	if (entity.m_Type != GE_ENTITY_TYPE_INDEXED_POINTS_BASIC)
//		return;
//
//	GL::UseProgram(entity.m_pShader->GetId());
//	GL::BindVertexArray(entity.m_VAO);
//	
//	// Wrap this into safe gl handler.
//	glDrawElements(GL_TRIANGLES, entity.m_NumIndices, GL_UNSIGNED_INT, (void*)0);
//	HandleError(__FUNCTION__);
//}
//
//void DrawPos3f(EntityPtr spEntity)
//{
//	if (spEntity->m_Type != GE_ENTITY_TYPE_POS3F)
//		return;
//
//	GL::UseProgram(spEntity->m_pShader->GetId());
//	GL::BindVertexArray(spEntity->m_VAO);
//	GL::DrawArrays(GL_TRIANGLES, 0, spEntity->m_NumVertices);
//}
//
//void DrawTriangle3DRGB(const Entity& entity)
//{
//	if (entity.m_Type != GE_ENTITY_TYPE_POS3F_COL3F)
//		return;
//
//	GL::UseProgram(entity.m_pShader->GetId());
//	GL::BindVertexArray(entity.m_VAO);
//	GL::DrawArrays(GL_TRIANGLES, 0, 3);
//}
//
//auto CreateVAO_IndexedPoints3DBasic(unsigned long long vertexBytes, float* vertices, unsigned long long indexBytes, unsigned int* indices) -> GLuint
//{
//	GLuint vao;
//	GL::GenVertexArrays(1, &vao);
//	GL::BindVertexArray(vao);
//
//	std::array<GLuint, 2> buffers;
//	GL::GenBuffers(2, buffers.data());
//
//	GL::BindBuffer(GL_ARRAY_BUFFER, buffers[0]);
//	GL::BufferData(GL_ARRAY_BUFFER, vertexBytes, vertices, GL_STATIC_DRAW);
//	GL::VertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
//	GL::EnableVertexAttribArray(0);
//
//	GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
//	GL::BufferData(GL_ELEMENT_ARRAY_BUFFER, indexBytes, indices, GL_STATIC_DRAW);
//
//	return vao;
//}
//
//auto GEengine::AddEntity() -> EntityPtr
//{
//	EntityPtr spEntity = std::make_shared<Entity>();
//	spEntity->m_Id = NextAvailableEntityId();
//	m_Entities.insert(spEntity);
//	return spEntity;
//}
//
//auto GEengine::GenerateEntity_IndexedPoints3DBasic(unsigned long long numVertexBytes, float* vertices, unsigned long long numIndexBytes, unsigned int* indices) -> unsigned int
//{
//	Entity entity;
//	entity.m_Type = GE_ENTITY_TYPE_INDEXED_POINTS_BASIC;
//	entity.m_Id = NextAvailableEntityId();
//	entity.m_pShader = m_Shaders[NamedShaderTriangleBasic];
//	entity.m_VAO = CreateVAO_IndexedPoints3DBasic(numVertexBytes, vertices, numIndexBytes, indices);
//	entity.m_NumIndices = static_cast<int>(numIndexBytes / sizeof(unsigned int));
//	//m_Entities.insert(entity);
//	return entity.m_Id;
//}
//
//auto GEengine::GetCurrentShaderProgram() -> GEshader*
//{
//	GLint prog;
//	GL::GetIntegerv(GL_CURRENT_PROGRAM, &prog);
//	auto it = std::find_if(m_Shaders.begin(), m_Shaders.end(), [&prog](const std::pair<std::string, GEshader*>& nameAndShader) 
//		{
//			return static_cast<int>(nameAndShader.second->GetId()) == prog;
//		});
//
//	if (it == m_Shaders.end())
//		return 0;
//	else
//		return it->second;
//}
//
//auto GEengine::GetRecentLogMessages(int* /*numMessages*/, const char*** /*messages*/) -> void
//{
//	//auto sinks = spdlog::get("Engine")->sinks();
//	//for (auto sink : sinks)
//	//{
//	//	if (auto spRingbuffer = std::dynamic_pointer_cast<spdlog::sinks::ringbuffer_sink_mt>(sink))
//	//	{
//	//		if (!m_LogMessages.empty())
//	//		{
//	//			for (auto& pStr : m_LogMessages)
//	//			{
//	//				delete[] pStr;
//	//			}
//
//	//			m_LogMessages.clear();
//	//		}
//
//	//		auto strings = spRingbuffer->last_formatted();
//	//		*numMessages = strings.size();
//	//		for (int i = 0; i < strings.size(); ++i)
//	//		{
//	//			auto sizeOfString = strings[i].size();
//	//			char* newString = new char[sizeOfString + 1];
//	//			std::fill(newString, newString + sizeOfString + 1, '\0');
//	//			std::copy(strings[i].begin(), strings[i].end(), newString);
//	//			m_LogMessages.push_back(newString);
//	//		}
//	//		
//	//		if (!m_LogMessages.empty())
//	//			*messages = m_LogMessages.data();
//	//	}
//	//}
//}
//
//auto GEengine::GetShader(const std::string& name) -> GEshader*
//{
//	if (!m_Shaders.contains(name))
//		return nullptr;
//
//	return m_Shaders.at(name);
//}
//
//auto GEengine::GetVAO(const std::string& name) -> GLuint
//{
//	if (!m_VAOs.contains(name))
//		return 0;
//	
//	return m_VAOs.at(name);
//}
//
//auto GEengine::Render() const -> void
//{
//	GL::Clear(GL_COLOR_BUFFER_BIT);
//	for (auto spEntity : m_Entities)
//	{
//		switch (spEntity->m_Type)
//		{
//		case GE_ENTITY_TYPE_INDEXED_POINTS_BASIC:
//			DrawIndexedPoints3DBasic(*spEntity);
//			break;
//		case GE_ENTITY_TYPE_POS3F:
//		case GE_ENTITY_TYPE_POS3F_COL3F:
//			GL::UseProgram(spEntity->m_pShader->GetId());
//			GL::BindVertexArray(spEntity->m_VAO);
//			GL::DrawArrays(GL_TRIANGLES, 0, spEntity->m_NumVertices);
//			break;
//		default:
//			BREAKPOINT; // We apparently need to support a new type.
//			break;
//		}
//	}
//}
//
//auto GEengine::SetEntityShader(unsigned int entId, GEshader* pShader) -> void
//{
//	auto it = std::find_if(m_Entities.begin(), m_Entities.end(), [&entId](EntityPtr spEntity) { return spEntity->m_Id == entId; });
//	if (it == m_Entities.end())
//	{
//		BREAKPOINT;
//		return;
//	}
//
//	(*it)->m_pShader = pShader;
//}
//
////auto GEengine::InitializeShaderTriangleBasic() -> bool
////{
////	auto pShader = geCreateShaderFromFiles("shaders/A0Pos3f.vert", nullptr, "shaders/ColorIs008033.frag");
////	if (!pShader)
////		return false;
////
////	m_Shaders.insert(std::make_pair(NamedShaderTriangleBasic, pShader));
////	return true;
////}
//
////auto GEengine::InitializeShaderTriangleRGB() -> bool
////{
////	auto pShader = geCreateShaderFromFiles("shaders/A0Pos3fA1Dummy3f.vert", nullptr, "shaders/A1RGB.frag");
////	if (!pShader)
////		return false;
////
////	m_Shaders.insert(std::make_pair(NamedShaderTriangleRGB, pShader));
////	return true;
////}
//
//auto GEengine::InitializeShaders() -> bool
//{
//	if (!InitializeShaderTriangleBasic())
//		return false;
//
//	if (!InitializeShaderTriangleRGB())
//		return false;
//
//	return true;
//}
//
//auto GEengine::InitializeLogging() -> bool
//{
//	std::vector<spdlog::sink_ptr> sinks;
//
//	// A rotating file sink provides logging that can be viewed in a text editor after the engine shuts down.
//
//	auto spRotatingFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs\\GraphicsEngine.log", 1024 * 1024 * 5, 3);
//	if (!spRotatingFileSink)
//		return false;
//
//	sinks.push_back(spRotatingFileSink);
//
//	// A ringbuffer sink keeps 128 messages in memory to be accessed by any client of the engine during runtime.
//
//	auto spRingbufferSink = std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(128);
//	if (!spRingbufferSink)
//		return false;
//
//	sinks.push_back(spRingbufferSink);
//
//	// Create a logger with our sinks.
//
//	auto spLogger = std::make_shared<spdlog::logger>("Engine", std::begin(sinks), std::end(sinks));
//	if (!spLogger)
//		return false;
//
//	spdlog::register_logger(spLogger);
//	spLogger->set_level(spdlog::level::debug);
//
//	return true;
//}
//
//auto GEengine::InitializeOpenGL() -> bool
//{
//	return (gladLoadGL() != 0);
//}
//
//auto GEengine::NextAvailableEntityId() const -> unsigned int
//{
//	unsigned int id = 1;
//
//	auto EntityHasId = [&id](const EntityPtr entity)
//		{
//			return entity->m_Id == id;
//		};
//
//	while (std::find_if(m_Entities.begin(), m_Entities.end(), EntityHasId) != m_Entities.end())
//	{
//		id++;
//	}
//
//	return id;
//}

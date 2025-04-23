#include "Engine.h"

#include "Attribute.h"
#include "Entity.h"
#include "Log.h"
#include "SafeGL.h"
#include "Shader.h"
#include "Texture.h"

namespace GraphicsEngine
{

	auto CreateEngine() -> IEnginePtr
	{
		return std::make_shared<Engine>();
	}

	Engine::Engine()
		: m_spLog(CreateLog())
	{
		if (gladLoadGL() == 0)
			m_spLog->Critical("Failed to load OpenGL.");

		std::stringstream ss;
		ss << "Initialized OpenGL.\n";
		ss << "OpenGL Version: " << glGetString(GL_VERSION) << '\n';
		ss << "OpenGL Vendor: " << glGetString(GL_VENDOR) << '\n';
		ss << "OpenGL Renderer: " << glGetString(GL_RENDERER) << '\n';
		ss << "GSLS Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION);
		m_spLog->Info(ss.str());

		GL::ClearColor(0.f, 0.f, 0.f, 1.f);
		GL::Clear(GL_COLOR_BUFFER_BIT);
	}

	Engine::~Engine()
	{
		spdlog::shutdown();
	}

	auto Engine::CreateNewEntity(const IAttributes& attributes, const std::vector<unsigned int>& indices) -> IEntityPtr
	{
		size_t numAttributes = attributes.size();

		GLuint vao;
		GL::GenVertexArrays(1, &vao);
		GL::BindVertexArray(vao);

		std::vector<GLuint> buffers(numAttributes);
		GL::GenBuffers(static_cast<GLsizei>(numAttributes), buffers.data());

		for (size_t i = 0; i < numAttributes; ++i)
		{
			AttributePtr spAttribute = std::dynamic_pointer_cast<Attribute>(attributes[i]);
			GL::BindBuffer(GL_ARRAY_BUFFER, buffers[i]);
			GL::BufferData(GL_ARRAY_BUFFER, spAttribute->GetNumBytes(), static_cast<const void*>(spAttribute->GetData().data()), GL_STATIC_DRAW);
			auto index = static_cast<GLuint>(i);
			GL::VertexAttribPointer(index, spAttribute->GetNumComponents(), spAttribute->GetType(), GL_FALSE, spAttribute->GetStride(), nullptr);
			GL::EnableVertexAttribArray(index);
		}

		if (!indices.empty())
		{
			GLuint eboBuffer;
			GL::GenBuffers(1, &eboBuffer);
			GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboBuffer);
			GL::BufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		}

		EntityPtr spEntity = CreateEntity();
		spEntity->SetVAO(vao);
		spEntity->SetNumVertices(std::dynamic_pointer_cast<Attribute>(attributes[0])->GetNumVertices());
		spEntity->SetNumIndices(indices.empty() ? 0 : static_cast<int>(indices.size()));

		m_Entities.push_back(spEntity);

		return std::dynamic_pointer_cast<IEntity>(spEntity);
	}

	auto Engine::CreateNewShaderFromFiles(const std::filesystem::path& vert, const std::filesystem::path& geom, const std::filesystem::path& frag) -> IShaderPtr
	{
		auto GetSourceFromFile = [this](const std::filesystem::path& path) -> std::string
		{
			if (path.empty())
				return "";

			if (!std::filesystem::exists(path))
			{
				m_spLog->Error(std::format("Could not open '{}' because it does not exist.", path.string()));
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

	auto Engine::CreateNewShaderFromSource(std::string_view vert, std::string_view geom, std::string_view frag) -> IShaderPtr
	{
		IShaderPtr spShader = CreateShaderFromSourceCode(vert, geom, frag);
		m_Shaders.push_back(spShader);
		return spShader;
	}

	auto Engine::CreateNewTextureFromFile(std::string_view textureName, const std::filesystem::path& path) -> ITexturePtr
	{
		ITexturePtr spTexture = CreateTextureFromFile(textureName, path);
		m_Textures.push_back(spTexture);
		return spTexture;
	}

	auto Engine::GetBackgroundColor() const -> Color
	{
		return m_BackgroundColor;
	}

	auto Engine::GetCurrentShader() const -> IShaderPtr
	{
		GLint id;
		GL::GetIntegerv(GL_CURRENT_PROGRAM, &id);
		auto it = std::ranges::find_if(m_Shaders, [&id](IShaderPtr spShader) 
		{
			return static_cast<int>(spShader->GetId()) == id;
		});

		if (it == m_Shaders.end())
			return nullptr;

		return *it;
	}

	auto Engine::GetLog() const -> ILogPtr
	{
		return m_spLog;
	}

	auto Engine::GetPolygonMode() const -> PolygonMode
	{
		return m_PolygonMode;
	}

	auto Engine::Render() const -> void
	{
		GL::Clear(GL_COLOR_BUFFER_BIT);
		for (auto spEntity : m_Entities)
		{
			auto spShader = spEntity->GetShader();
			if (!spShader)
				continue;	
			
			spShader->Use();
			auto textures = spEntity->GetTextures();
			for (size_t i = 0; i < textures.size(); ++i)
			{
				auto spTexture = std::dynamic_pointer_cast<Texture>(textures[i]);
				if (!spTexture)
					continue;
				
				GL::ActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
				GL::BindTexture(GL_TEXTURE_2D, spTexture->GetId());
				if (auto spUniform = spShader->GetActiveUniform(spTexture->GetName()))
					spUniform->SetData(static_cast<int>(i));
			}
			GL::BindVertexArray(spEntity->GetVAO());
			if (spEntity->GetNumIndices() > 0)
				GL::DrawElements(GL_TRIANGLES, spEntity->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
			else
				GL::DrawArrays(GL_TRIANGLES, 0, spEntity->GetNumVertices());
		}
	}

	auto Engine::SetBackgroundColor(const Color& color) -> void
	{
		m_BackgroundColor = color;
		GL::ClearColor(m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b, m_BackgroundColor.a);
	}

	auto Engine::SetPolygonMode(PolygonMode polygonMode) -> void
	{
		using enum GraphicsEngine::PolygonMode;
		
		m_PolygonMode = polygonMode;
		switch (m_PolygonMode)
		{
		case Fill:
			GL::PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case Line:
			GL::PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case Point:
			GL::PolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		}
	}

    auto Engine::GetNextAvailableEntityId() const -> unsigned int
    {
		unsigned int id = 1;

		auto IdIsTaken = [&id](IEntityPtr spEntity) 
		{ 
			return spEntity->GetId() == id; 
		};

		while (std::ranges::find_if(m_Entities, IdIsTaken) != m_Entities.end())
		{
		 	id++;
		}

		return id;
	}
}

#include "Engine.h"

#include "Attribute.h"
#include "Entity.h"
#include "Log.h"
#include "SafeGL.h"
#include "Texture.h"
#include "Uniform.h"

namespace GraphicsEngine
{

	auto CreateEngine() -> IEnginePtr
	{
		return std::make_shared<Engine>();
	}

	Engine::Engine()
		:	m_upEntityManagerImpl(CreateEntityManagerImpl(this)),
			m_upShaderManagerImpl(CreateShaderManagerImpl(this)),
			m_spLog(CreateLog())
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

		GL::Enable(GL_DEPTH_TEST);

		GL::ClearColor(0.f, 0.f, 0.f, 1.f);
		GL::Clear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	}

	Engine::~Engine()
	{
		spdlog::shutdown();
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

	auto Engine::GetCamera() const -> ICameraPtr
	{
		return m_spCamera;
	}

	auto Engine::GetEntityManager() -> EntityManager*
	{
		return m_upEntityManagerImpl.get();
	}

	auto Engine::GetLog() const -> ILogPtr
	{
		return m_spLog;
	}

	auto Engine::GetPolygonMode() const -> PolygonMode
	{
		return m_PolygonMode;
	}

	auto Engine::GetShaderManager() -> ShaderManager*
	{
		return m_upShaderManagerImpl.get();
	}

	auto Engine::Render() -> void
	{
		GL::Clear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		for (auto entId : m_upEntityManagerImpl->GetEntityIds())
		{
			auto pEntity = m_upEntityManagerImpl->GetEntity(entId);

			auto shaderId = pEntity->shaderId;
			m_upShaderManagerImpl->UseShader(shaderId);
			m_upShaderManagerImpl->SetUniformData(shaderId, "model", pEntity->modelMatrix);
			if (m_spCamera)
			{
				m_upShaderManagerImpl->SetUniformData(shaderId, "view", m_spCamera->GetViewMatrix());
				m_upShaderManagerImpl->SetUniformData(shaderId, "projection", m_spCamera->GetProjectionMatrix());
			}

			auto textures = pEntity->textures;
			for (size_t i = 0; i < textures.size(); ++i)
			{
				auto spTexture = std::dynamic_pointer_cast<Texture>(textures[i]);
				if (!spTexture)
					continue;
				
				GL::ActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
				GL::BindTexture(GL_TEXTURE_2D, spTexture->GetId());
				m_upShaderManagerImpl->SetUniformData(shaderId, spTexture->GetName(), static_cast<int>(i));
			}
			GL::BindVertexArray(pEntity->vao);
			if (pEntity->numIndices > 0)
				GL::DrawElements(GL_TRIANGLES, pEntity->numIndices, GL_UNSIGNED_INT, nullptr);
			else
				GL::DrawArrays(GL_TRIANGLES, 0, pEntity->numVertices);
		}
	}

	auto Engine::ResizeViewport(int width, int height) -> void
	{
		GL::Viewport(0, 0, width, height);

		if (auto spCamera = GetCamera())
		{
			float aspect = static_cast<float>(width) / static_cast<float>(height);
			GetCamera()->SetAspectRatio(aspect);
		}
	}

	auto Engine::SetBackgroundColor(const Color& color) -> void
	{
		m_BackgroundColor = color;
		GL::ClearColor(m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b, m_BackgroundColor.a);
	}

	auto Engine::SetCamera(ICameraPtr spCamera) -> void
	{
		m_spCamera = spCamera;
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

}

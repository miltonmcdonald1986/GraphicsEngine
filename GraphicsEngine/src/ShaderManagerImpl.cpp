#include "ShaderManagerImpl.h"

#include "Fwd.h"
#include "IEngine.h"
#include "Log.h"
#include "SafeGL.h"
#include "ShaderImpl.h"
#include "ShaderUtilities.h"
#include "Uniform.h"

// 0. FRAGMENT_SHADER_SOURCE;
// 1. GEOMETRY_SHADER_SOURCE;
// 2. ID;
// 3. UNIFORM_NAMES;
// 4. VERTEX_SHADER_SOURCE;

namespace graphics_engine
{

	namespace Helpers
	{

		auto ErrorMessageShaderWithIdDoesNotExist (Types::ShaderId id) -> Types::String
		{
			return std::format ("Shader with id {} does not exist.", id);
		}

	}

	ShaderManagerImpl::ShaderManagerImpl (IEngine* pEngine)
		: m_pEngine (pEngine)
	{
	}

	auto ShaderManagerImpl::AddShaderFromFiles (const Types::Path& vert, const Types::Path& frag, const Types::OptPath& oGeom) -> Shader*
	{
		auto vertSource = ShaderUtilities::GetSourceFromFile (vert);
		auto fragSource = ShaderUtilities::GetSourceFromFile (frag);
		std::optional<Types::String> oGeomSource = oGeom ? std::optional<Types::String> (ShaderUtilities::GetSourceFromFile (*oGeom)) : std::nullopt;
		ShaderImpl shader (vertSource, fragSource, oGeomSource);
		m_Shaders.try_emplace (shader.ID, shader);
		return &m_Shaders.at(shader.ID);
	}

	auto ShaderManagerImpl::AddShaderFromSource (const Types::StringView& vert, const Types::StringView& frag, const Types::OptStringView& oGeom) -> Shader*
	{
		ShaderImpl shader (vert, frag, oGeom);
		m_Shaders.try_emplace (shader.ID, shader);
		return &m_Shaders.at (shader.ID);
	}

	auto ShaderManagerImpl::GetCurrentShader () -> Shader*
	{
		GLint id;
		GL::GetIntegerv (GL_CURRENT_PROGRAM, &id);
		if (m_Shaders.contains (id))
			return &m_Shaders.at (id);
		else
			return nullptr;
	}

	auto ShaderManagerImpl::GetShader (Types::ShaderId id) -> Shader*
	{
		if (m_Shaders.contains (id))
			return &m_Shaders.at (id);
		else
			return nullptr;
	}

	auto CreateShaderManagerImpl (IEngine* pEngine) -> ShaderManagerImplPtr
	{
		return std::make_unique<ShaderManagerImpl> (pEngine);
	}

}

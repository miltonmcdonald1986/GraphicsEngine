#pragma once

#include "Shader.h"
#include "Types.h"
#include "Uniform.h"

namespace graphics_engine
{

	class ShaderImpl : public Shader
	{
	public:

		ShaderImpl () = delete;
		
		ShaderImpl (
			Types::StringView vert, 
			Types::StringView frag, 
			Types::OptStringView oGeom = std::nullopt
		);

		explicit ShaderImpl (const std::tuple<Types::StringView, Types::OptStringView, Types::ShaderId, Uniforms, Types::StringView>& data);

		auto GetUniformData (Types::StringView name) const -> std::optional<Types::UniformData> override;

		auto SetUniformData (Types::StringView name, const Types::UniformData& data) -> bool override;

		auto Use () const -> void override;

		Uniforms m_Uniforms;
	};

}

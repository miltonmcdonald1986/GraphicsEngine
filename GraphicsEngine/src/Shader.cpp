#include "Shader.h"

#include "Log.h"
#include "SafeGL.h"

namespace GraphicsEngine
{

	//Shader::Shader(StringView vertSource, std::string_view fragSource, std::optional<StringView> oGeomSource)
	//	: id(Helpers::CompileShadersAndLinkProgram(vertSource, fragSource, oGeomSource))
	//{
	//	// Grab the list of uniforms from the shader.
	//	GLint count;
	//	GL::GetProgramiv(id, GL_ACTIVE_UNIFORMS, &count);

	//	GLint maxLength;
	//	GL::GetProgramiv(id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);

	//	m_Uniforms.clear();
	//	for (int i = 0; i < count; ++i)
	//	{
	//		GLint size;
	//		GLenum type;
	//		std::string name(maxLength, '\0');
	//		GLsizei length; // name length
	//		GL::GetActiveUniform(id, i, maxLength, &length, &size, &type, name.data());
	//		name.resize(strlen(name.c_str()));

	//		GLint location = GL::GetUniformLocation(id, name.data());

	//		Uniform uniform(name, location);
	//		m_Uniforms.push_back(uniform);

	//		switch (type)
	//		{
	//		case GL_FLOAT:
	//		{
	//			float data;
	//			GL::GetUniformfv(id, location, &data);
	//			SetUniformData(name, data);
	//			break;
	//		}
	//		case GL_FLOAT_VEC4:
	//		{
	//			std::array<float, 4> v;
	//			GL::GetUniformfv(id, location, v.data());
	//			glm::vec4 data(v[0], v[1], v[2], v[3]);
	//			SetUniformData(name, data);
	//			break;
	//		}
	//		case GL_FLOAT_MAT4:
	//		{
	//			glm::mat4 m;
	//			GL::GetUniformfv(id, location, glm::value_ptr(m));
	//			SetUniformData(name, m);
	//			break;
	//		}
	//		case GL_SAMPLER_2D:
	//		{
	//			int data;
	//			GL::GetUniformiv(id, location, &data);
	//			SetUniformData(name, data);
	//			break;
	//		}
	//		default:
	//		{
	//			GetLog()->Warn(std::format("Shader uniform type not handled: {}", type));
	//			break;
	//		}
	//		}
	//	}
	//}

  //  auto Shader::GetActiveUniform(std::string_view name) -> Uniform*
  //  {
  //      auto it = std::ranges::find_if(m_Uniforms, [&name](const Uniform& uniform)
		//{ 
		//	return uniform.name == name; 
		//});

		//if (it != m_Uniforms.end())
		//	return &(*it);
		//else
		//	return nullptr;
  //  }

 //   auto Shader::GetActiveUniformNames () const -> StringViews
	//{
	//	StringViews names(m_Uniforms.size());
	//	std::ranges::transform(m_Uniforms, names.begin(), [](const Uniform& uniform) -> StringView { return uniform.name; });
	//	return names;
	//}

	//auto Shader::SetUniformData(StringView name, const UniformData& data) -> void
	//{
	//	auto pUniform = GetActiveUniform(name);
	//	if (!pUniform)
	//		return;

	//	pUniform->data = data;
	//	
	//	const auto location = pUniform->location;
	//	GL::UseProgram(id);
	//	if (std::holds_alternative<float>(data))
	//		GL::Uniform1f(location, std::get<float>(data));
	//	else if (std::holds_alternative<glm::mat4x4>(data))
	//		GL::UniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(std::get<glm::mat4>(data)));
	//	else if (std::holds_alternative<glm::vec4>(data))
	//	{
	//		auto v = std::get<glm::vec4>(data);
	//		GL::Uniform4f(location, v[0], v[1], v[2], v[3]);
	//	}
	//	else if (std::holds_alternative<int>(data))
	//		GL::Uniform1i(location, std::get<int>(data));
	//	else
	//		GetLog()->Warn("Data type not handled by Uniform::SetData.");
	//}

}

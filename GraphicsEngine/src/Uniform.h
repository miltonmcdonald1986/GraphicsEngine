#pragma once

#include "IUniform.h"

#include "Fwd.h"

namespace GraphicsEngine
{

	class Uniform : public IUniform
	{
	public:
		explicit Uniform(GLuint programId);
		~Uniform() override = default;

		auto GetData() const->Data override;
		auto GetLocation() const -> int override;
		auto GetName() const->std::string override;
		auto SetData(const Data& data) -> void override;
		auto SetLocation(GLint location) -> void;
		auto SetName(std::string_view name) -> void;

	private:
		Data m_Data = 0.f;
		GLint m_Location = 0;
		std::string m_Name = "";
		GLuint m_ProgramId = 0;
	};

	auto CreateUniform(GLuint programId) -> UniformPtr;

}

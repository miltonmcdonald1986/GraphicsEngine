#pragma once

#include "IUniform.h"

#include "Fwd.h"

namespace GraphicsEngine
{

	class Uniform : public IUniform
	{
	public:
		virtual ~Uniform() override = default;

		virtual auto GetData() const->Data override;
		virtual auto GetLocation() const -> int override;
		virtual auto GetName() const->std::string override;
		virtual auto SetData(const Data& data) -> void override;
		auto SetLocation(GLint location) -> void;
		auto SetName(const std::string& name) -> void;

	private:
		Data m_Data = 0.f;
		GLint m_Location = 0;
		std::string m_Name = "";
	};

	auto CreateUniform() -> UniformPtr;

}

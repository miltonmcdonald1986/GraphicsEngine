#pragma once

#include <array>
#include <memory>
#include <stdexcept>

#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine
{

	class GRAPHICSENGINE_API Color
	{
	public:
		
		Color(float r, float g, float b, float a = 1.f);
		Color(float rgba[4]);
		Color(const Color& other);
		~Color();

		float& operator[](int index);
		const float& operator[](int index) const;
		
		float* operator*();


	private:

#pragma warning( push )
#pragma warning( disable : 4251 )

		struct Impl;
		std::unique_ptr<Impl> m_upImpl;

#pragma warning( pop )
		
	};

}

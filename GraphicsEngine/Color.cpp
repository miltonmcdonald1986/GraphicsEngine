#include "pch.h"
#include "Color.h"

#include <algorithm>
#include <stdexcept>

namespace GraphicsEngine
{
	struct Color::Impl
	{
		Impl(float r, float g, float b, float a)
		{
			m_RGBA[0] = r;
			m_RGBA[1] = g;
			m_RGBA[2] = b;
			m_RGBA[3] = a;
		}

		float& operator[](int index)
		{
			if (index >= 0 && index < 4) {
				return m_RGBA[index];
			}
			throw std::out_of_range("Index out of bounds");
		}

		const float& operator[](int index) const
		{
			if (index >= 0 && index < 4) {
				return m_RGBA[index];
			}
			throw std::out_of_range("Index out of bounds");
		}

		float* operator*()
		{
			return m_RGBA.data();
		}

		std::array<float, 4> m_RGBA = { 0.f, 0.f, 0.f, 1.f };
	};

	Color::Color(float r, float g, float b, float a)
		: m_upImpl(std::unique_ptr<Impl>(new Impl(r, g, b, a)))
	{
	}

	Color::Color(float color[4])
		: Color(color[0], color[1], color[2], color[3])
	{
	}

	Color::Color(const Color& other)
		: m_upImpl(std::unique_ptr<Impl>(new Impl(*other.m_upImpl)))
	{
	}

	Color::~Color()
	{
	}

	float& Color::operator[](int index)
	{
		return (*m_upImpl)[index];
	}

	const float& Color::operator[](int index) const
	{
		return (*m_upImpl)[index];
	}

	float* Color::operator*()
	{
		return **m_upImpl;
	}

}

#pragma once

#include <memory>

namespace GraphicsEngine
{

	struct Entity;
	using EntityPtr = std::shared_ptr<Entity>;

	class Uniform;
	using UniformPtr = std::shared_ptr<Uniform>;

}

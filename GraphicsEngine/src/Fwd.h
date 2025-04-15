#pragma once

#include <memory>

namespace GraphicsEngine
{

	class Attribute;
	class Entity;
	class Uniform;
	
	using AttributePtr = std::shared_ptr<Attribute>;
	using EntityPtr = std::shared_ptr<Entity>;
	using UniformPtr = std::shared_ptr<Uniform>;

}

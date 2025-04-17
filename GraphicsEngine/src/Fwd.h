#pragma once

#include <memory>

namespace spdlog
{

	class logger;

}

using loggerPtr = std::shared_ptr<spdlog::logger>;

namespace GraphicsEngine
{

	class Attribute;
	using AttributePtr = std::shared_ptr<Attribute>;
	
	class Entity;
	using EntityPtr = std::shared_ptr<Entity>;

	class Log;
	using LogPtr = std::shared_ptr<Log>;

	class Uniform;
	using UniformPtr = std::shared_ptr<Uniform>;

}

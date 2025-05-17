#pragma once

#include <expected>
#include <variant>
#include <vector>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include "Error.h"

namespace graphics_engine{

using Attribute = std::variant<
	std::vector<glm::vec2>,
	std::vector<glm::vec3>
>;

using Attributes = std::vector<Attribute>;
using ExpectAttribute = std::expected<Attribute, Error>;

}

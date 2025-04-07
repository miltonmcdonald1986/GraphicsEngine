#pragma once

#include <memory>

class Widget;
using WidgetUniquePointer = std::unique_ptr<Widget>;

struct GEengine;
using GEengineSharedPtr = std::shared_ptr<GEengine>;

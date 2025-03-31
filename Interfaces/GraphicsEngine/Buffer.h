#pragma once

#include "GraphicsEngine/GL.h"
#include "GraphicsEngine/Log.h"
#include "GraphicsEngine/GraphicsEngineImpExp.h"

namespace GraphicsEngine
{

	//struct GRAPHICSENGINE_API DataStore
	//{

	//	GL::BufferBindingTarget m_Target = GL::BufferBindingTarget::Array;
	//	signed long long int m_NumBytes = 0;
	//	const void* m_pData = nullptr;
	//	GL::DataUsagePattern m_Usage = GL::DataUsagePattern::StaticDraw;
	//	GL::AttributeSize m_NumComponents = GL::AttributeSize::Three;
	//	GL::DataType m_DataType = GL::DataType::Float;
	//	bool normalized = false;
	//};

	//class GRAPHICSENGINE_API Buffer
	//{
	//public:
	//	Buffer(const DataStore& dataStore);
	//	auto Bind() const -> bool;
	//	auto GetDataStore() const -> DataStore;
	//	auto GetId() const -> unsigned int;

	//private:
	//	DataStore m_DataStore;
	//	unsigned int m_BufferId = 0;
	//};

}

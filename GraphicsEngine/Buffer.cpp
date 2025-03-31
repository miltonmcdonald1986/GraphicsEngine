#include "pch.h"
#include "GraphicsEngine/Buffer.h"

#include "GraphicsEngine/Log.h"

namespace 
{

//	auto ConvertBufferBindingTargetToGLenum(GraphicsEngine::GL::BufferBindingTarget target) -> GLenum
//	{
//		switch (target)
//		{
//		case GraphicsEngine::GL::BufferBindingTarget::Array:
//			return GL_ARRAY_BUFFER;
//		case GraphicsEngine::GL::BufferBindingTarget::CopyRead:
//			return GL_COPY_READ_BUFFER;
//		case GraphicsEngine::GL::BufferBindingTarget::CopyWrite:
//			return GL_COPY_WRITE_BUFFER;
//		case GraphicsEngine::GL::BufferBindingTarget::ElementArray:
//			return GL_ELEMENT_ARRAY_BUFFER;
//		case GraphicsEngine::GL::BufferBindingTarget::PixelPack:
//			return GL_PIXEL_PACK_BUFFER;
//		case GraphicsEngine::GL::BufferBindingTarget::PixelUnpack:
//			return GL_PIXEL_UNPACK_BUFFER;
//		case GraphicsEngine::GL::BufferBindingTarget::Texture:
//			return GL_TEXTURE_BUFFER;
//		case GraphicsEngine::GL::BufferBindingTarget::TransformFeedback:
//			return GL_TRANSFORM_FEEDBACK_BUFFER;
//		case GraphicsEngine::GL::BufferBindingTarget::Uniform:
//			return GL_UNIFORM_BUFFER;
//		default:
//		{
//			LOG_ERROR("Unknown buffer binding target.");
//			return GL_INVALID_ENUM;
//		}
//		}
//	}
//
//}
//
//namespace GraphicsEngine
//{
//
//	Buffer::Buffer(const DataStore& dataStore)
//		: m_DataStore(dataStore)
//	{
//		glGenBuffers(1, &m_BufferId);
//		if (GL_ERROR())
//		{
//			LOG_ERROR("Could not generate buffer.");
//			return;
//		}
//
//		GLenum target = ConvertBufferBindingTargetToGLenum(m_DataStore.m_Target);
//
//		glBindBuffer(target, m_BufferId);
//		if (GL_ERROR())
//		{
//			LOG_ERROR("Could not bind buffer.");
//			return;
//		}
//
//		GLenum usage;
//		switch (m_DataStore.m_Usage)
//		{
//		case GraphicsEngine::GL::DataUsagePattern::StreamDraw:
//			usage = GL_STREAM_DRAW;
//			break;
//		case GraphicsEngine::GL::DataUsagePattern::StreamRead:
//			usage = GL_STREAM_READ;
//			break;
//		case GraphicsEngine::GL::DataUsagePattern::StreamCopy:
//			usage = GL_STREAM_COPY;
//			break;
//		case GraphicsEngine::GL::DataUsagePattern::StaticDraw:
//			usage = GL_STATIC_DRAW;
//			break;
//		case GraphicsEngine::GL::DataUsagePattern::StaticRead:
//			usage = GL_STATIC_READ;
//			break;
//		case GraphicsEngine::GL::DataUsagePattern::StaticCopy:
//			usage = GL_STATIC_COPY;
//			break;
//		case GraphicsEngine::GL::DataUsagePattern::DynamicDraw:
//			usage = GL_DYNAMIC_DRAW;
//			break;
//		case GraphicsEngine::GL::DataUsagePattern::DynamicRead:
//			usage = GL_DYNAMIC_READ;
//			break;
//		case GraphicsEngine::GL::DataUsagePattern::DynamicCopy:
//			usage = GL_DYNAMIC_COPY;
//			break;
//		default:
//		{
//			LOG_ERROR("Unknown data usage pattern.");
//			return;
//		}
//		}
//
//		glBufferData(target, m_DataStore.m_NumBytes, m_DataStore.m_pData, usage);
//		if (GL_ERROR())
//		{
//			LOG_ERROR("Could not initialize buffer object's data store.");
//			return;
//		}
//	}
//
//	auto Buffer::Bind() const -> bool
//	{
//		glBindBuffer(ConvertBufferBindingTargetToGLenum(m_DataStore.m_Target), m_BufferId);
//		if (GL_ERROR())
//		{
//			LOG_ERROR("Could not bind buffer.");
//			return false;
//		}
//
//		return true;
//	}
//
//	auto Buffer::GetDataStore() const -> DataStore
//	{
//		return m_DataStore;
//	}
//
//	auto Buffer::GetId() const -> unsigned int
//	{
//		return m_BufferId;
//	}

}

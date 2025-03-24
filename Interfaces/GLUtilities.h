#pragma once

#include <vector>

#include "glad/glad.h"

#include "spdlog/spdlog.h"

#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine::Utilities
{
	
#pragma region Enumerations

	/// <summary>
	/// Specifies the number of components per generic vertex attribute.
	/// </summary>
	enum class AttributeSize : GLint
	{
		One		= 1,
		Two		= 2,
		Three	= 3,
		Four	= 4,
		BGRA	= GL_BGRA
	};

	/// <summary>
	/// Buffer binding targets
	/// </summary>
	enum class BufferBindingTarget : GLenum
	{
		/// <summary>
		/// Vertex Attributes
		/// </summary>
		Array = GL_ARRAY_BUFFER,
		
		/// <summary>
		/// Buffer copy source
		/// </summary>
		CopyRead = GL_COPY_READ_BUFFER,

		/// <summary>
		/// Buffer copy destination
		/// </summary>
		CopyWrite = GL_COPY_WRITE_BUFFER,

		/// <summary>
		/// Vertex array indices
		/// </summary>
		ElementArray = GL_ELEMENT_ARRAY_BUFFER,

		/// <summary>
		/// Pixel read target
		/// </summary>
		PixelPack = GL_PIXEL_PACK_BUFFER,

		/// <summary>
		/// Texture data source
		/// </summary>
		PixelUnpack = GL_PIXEL_UNPACK_BUFFER,

		/// <summary>
		/// Texture data buffer
		/// </summary>
		Texture = GL_TEXTURE_BUFFER,

		/// <summary>
		/// Transform feedback buffer
		/// </summary>
		TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,

		/// <summary>
		/// Uniform bloxk storage
		/// </summary>
		Uniform = GL_UNIFORM_BUFFER
	};

	/// <summary>
	/// Specifies a data type
	/// </summary>
	enum class DataType : GLenum
	{
		Byte						= GL_BYTE,
		UnsignedByte				= GL_UNSIGNED_BYTE,
		Short						= GL_SHORT,
		UnsignedShort				= GL_UNSIGNED_SHORT,
		Int							= GL_INT,
		UnsignedInt					= GL_UNSIGNED_INT,
		HalfFloat					= GL_HALF_FLOAT,
		Float						= GL_FLOAT,
		Double						= GL_DOUBLE,
		Int_2_10_10_10_Rev			= GL_INT_2_10_10_10_REV,
		UnsignedInt_2_10_10_10_Rev	= GL_UNSIGNED_INT_2_10_10_10_REV,
		UngisnedInt_10F_11F_11F_Rev	= GL_UNSIGNED_INT_10F_11F_11F_REV
	};

	/// <summary>
	/// A hint to the GL implementation as to how a buffer object's data store will be accessed.
	/// </summary>
	enum class DataUsagePattern : GLenum
	{
		/// <summary>
		/// Modified once, used at most a few times, modified by the application, 
		/// used as the source for GL drawing and image specification commands.
		/// </summary>
		StreamDraw = GL_STREAM_DRAW,

		/// <summary>
		/// Modified once, used at most a few times, modified by reading data from the GL, 
		/// used to return that data when queried by the application.
		/// </summary>
		StreamRead = GL_STREAM_READ,

		/// <summary>
		/// Modified once, used at most a few times, modified by reading data from the GL, 
		/// used as the source for GL drawing and image specification commands.
		/// </summary>
		StreamCopy = GL_STREAM_COPY,

		/// <summary>
		/// Modified once, used many times, modified by the application, 
		/// used as the source for GL drawing and image specification commands.
		/// </summary>
		StaticDraw = GL_STATIC_DRAW,

		/// <summary>
		/// Modified once, used many times, modified by reading data from the GL, 
		/// used to return that data when queried by the application.
		/// </summary>
		StaticRead = GL_STATIC_READ,

		/// <summary>
		/// Modified once, used many times, modified by reading data from the GL, 
		/// used as the source for GL drawing and image specification commands.
		/// </summary>
		StaticCopy = GL_STATIC_COPY,

		/// <summary>
		/// Modified repeatedly and used many times, modified by the application, 
		/// used as the source for GL drawing and image specification commands.
		/// </summary>
		DynamicDraw = GL_DYNAMIC_DRAW,

		/// <summary>
		/// Modified repeatedly and used many times, modified by reading data from the GL, 
		/// used to return that data when queried by the application.
		/// </summary>
		DynamicRead = GL_DYNAMIC_READ,

		/// <summary>
		/// Modified repeatedly and used many times, modified by reading data from the GL, 
		/// used as the source for GL drawing and image specification commands.
		/// </summary>
		DynamicCopy = GL_DYNAMIC_COPY
	};

#pragma endregion

#pragma region Functions

	/// <summary>
	/// Bind a named buffer object for the purpose of Vertex Attributes.
	/// </summary>
	/// <param name="buffer"> Specifies the name of a buffer object. </param>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto BindArrayBuffer(GLuint buffer) -> bool;

	/// <summary>
	/// Bind a named buffer object
	/// </summary>
	/// <param name="target"> Specifies the target to which the buffer object is bound. </param>
	/// <param name="buffer"> Specifies the name of a buffer object. </param>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto BindBuffer(BufferBindingTarget target, GLuint buffer) -> bool;

	/// <summary>
	/// Bind a vertex array object.
	/// </summary>
	/// <param name="array"> Specifies the name of the vertex array to bind. </param>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto BindVertexArray (GLuint array) -> bool;

	/// <summary>
	/// Creates and initializes a buffer object's data store.
	/// </summary>
	/// <param name="target"> Specifies the target to which the buffer object is bound. </param>
	/// <param name="size"> Specifies the size in bytes of the buffer object's new data store. </param>
	/// <param name="data"> Specifies a pointer to data that will be copied into the data store for 
	///						initialization, or nullptr if no data is to be copied. </param>
	/// <param name="usage"> Specifies the expected usage pattern of the data store. </param>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto BufferData(BufferBindingTarget target, GLsizeiptr size, const void* data, DataUsagePattern usage) -> bool;

	/// <summary>
	/// Creates and initializes a buffer object's data store with floats.
	/// </summary>
	/// <param name="target"> Specifies the target to which the buffer object is bound. </param>
	/// <param name="data"> A vector of floats that will be copied into the data store for initialization. </param>
	/// <param name="usage"> Specifies the expected usage pattern of the data store. </param>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto BufferFloatData(BufferBindingTarget target, const std::vector<float>& data, DataUsagePattern usage) -> bool;

	/// <summary>
	/// Enable a generic vertex attribute array.
	/// </summary>
	/// <param name="index"> Specifies the index of the generic vertex attribute to be enabled. </param>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto EnableVertexAttribArray(GLuint index) -> bool;

	/// <summary>
	/// Generate buffer object names.
	/// </summary>
	/// <param name="n"> Specifies the number of buffer object names to be generated. </param>
	/// <returns> A vector in which the generated buffer object names are stored. </returns>
	GRAPHICSENGINE_API auto GenBuffers(GLsizei n) -> std::vector<GLuint>;

	/// <summary>
	/// Generate a buffer object name.
	/// </summary>
	/// <returns> Upon success, a buffer object name; otherwise nullopt. </returns>
	GRAPHICSENGINE_API auto GenOneBuffer() -> std::optional<GLuint>;

	/// <summary>
	/// Generate a vertex array object name.
	/// </summary>
	/// <returns> On success, a vertex array object name; otherwise nullopt. </returns>
	GRAPHICSENGINE_API auto GenOneVertexArray () -> std::optional<GLuint>;

	/// <summary>
	/// Generate vertex array object names.
	/// </summary>
	/// <param name="n"> Specifies the number of vertex array object names to generate </param>
	/// <returns> A vector in which the generated vertex array object names are stored. </returns>
	GRAPHICSENGINE_API auto GenVertexArrays (GLsizei n) -> std::vector<GLuint>;

	/// <summary>
	/// Unbind any buffer object previously bound for the purpose of Vertex Attributes.
	/// </summary>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto UnbindArrayBuffer() -> bool;

	/// <summary>
	/// Unbind any buffer object previously bound.
	/// </summary>
	/// <param name="target"> Specifies the target to unbind. </param>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto UnbindBuffer(BufferBindingTarget target) -> bool;

	/// <summary>
	/// Break the existing vertex array object binding.
	/// </summary>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto UnbindVertexArray() -> bool;

	/// <summary>
	/// Define an array of generic vertex attribute data.
	/// </summary>
	/// <param name="index"> Specifies the index of the generic vertex attribute to be modified. </param>
	/// <param name="size"> Specifies the number of components per generic vertex attribute. </param>
	/// <param name="type"> Specifies the data type of each component in the array. </param>
	/// <param name="normalized"> Specifies whether fixed-point data values should be normalized. </param>
	/// <param name="stride"> Specifies the byte offset between consecutive generic vertex attributes. </param>
	/// <param name="offsetOfFirstComponent"> Specifies a offset of the first component of the first 
	///										  generic vertex attribute in the array in the data store 
	///										  of the buffer currently bound for the purpose of Vertex Attributes. </param>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto VertexAttribPointer(GLuint index, AttributeSize size, DataType type, bool normalized, GLsizei stride, int offsetOfFirstComponent) -> bool;

#pragma endregion

}

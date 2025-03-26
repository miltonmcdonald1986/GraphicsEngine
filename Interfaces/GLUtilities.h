#pragma once

#include <array>
#include <optional>
#include <string>
#include <vector>

#include "glad/glad.h"

#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine::GL::Utilities
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

	enum class ErrorFlag : GLenum
	{
		/// <summary>
		/// No error has been recorded.
		/// </summary>
		NoError = GL_NO_ERROR,
		
		/// <summary>
		/// An unacceptable value is specified for an enumerated argument.
		/// </summary>
		InvalidEnum = GL_INVALID_ENUM,
		
		/// <summary>
		/// A numeric argument is out of range.
		/// </summary>
		InvalidValue = GL_INVALID_VALUE,
		
		/// <summary>
		/// The specified operation is not allowed in the current state.
		/// </summary>
		InvalidOperation = GL_INVALID_OPERATION,
		
		/// <summary>
		/// The framebuffer object is not complete.
		/// </summary>
		InvalidFramebufferOperation = GL_INVALID_FRAMEBUFFER_OPERATION,
		
		/// <summary>
		/// There is not enough memory left to execute the command.
		/// </summary>
		OutOfMemory = GL_OUT_OF_MEMORY
	};

	enum class PolygonModeType : GLenum
	{
		Point	= GL_POINT,
		Line	= GL_LINE,
		Fill	= GL_FILL
	};

	/// <summary>
	/// Types of shader
	/// </summary>
	enum class ShaderType : GLenum
	{
		Vertex		= GL_VERTEX_SHADER,
		Geometry	= GL_GEOMETRY_SHADER,
		Fragment	= GL_FRAGMENT_SHADER
	};

#pragma endregion

#pragma region Functions

	/// <summary>
	/// Attaches a shader object to a program object.
	/// </summary>
	/// <param name="program"> Specifies the program object to which a shader object
	///                        will be attached. </param>
	/// <param name="shader"> Specifies the shader object that is to be attached. </param>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto AttachShader(GLuint program, GLuint shader) -> bool;

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
	/// Specify clear values for the color buffers.
	/// </summary>
	/// <param name="red"> Specify the red value used when the color buffers are cleared. </param>
	/// <param name="green"> Specify the green value used when the color buffers are cleared. </param>
	/// <param name="blue"> Specify the blue value used when the color buffers are cleared. </param>
	/// <param name="alpha"> Specify the alpha value used when the color buffers are cleared. </param>
	GRAPHICSENGINE_API auto ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha = 1.f) -> void;

	/// <summary>
	/// Clear the color buffers to preset values.
	/// </summary>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto ClearColorBuffers() -> bool;

	/// <summary>
	/// Compiles a shader object.
	/// </summary>
	/// <param name="shader"> Specifies the shader object to be compiled. </param>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto CompileShader(GLuint shader) -> bool;

	/// <summary>
	/// Creates a program object.
	/// </summary>
	/// <returns> A handle to the program object that was created. </returns>
	GRAPHICSENGINE_API auto CreateProgram() -> std::optional<GLuint>;

	/// <summary>
	/// Creates a shader object.
	/// </summary>
	/// <param name="type"> Specifies the type of shader to be created. </param>
	/// <returns> A shader object, if it succeeds; nullopt otherwise. </returns>
	GRAPHICSENGINE_API auto CreateShader(ShaderType type) -> std::optional<GLuint>;

	/// <summary>
	/// Deletes a shader object.
	/// </summary>
	/// <param name="shader"> Specifies the shader object to be deleted. </param>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto DeleteShader(GLuint shader) -> bool;

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
	/// Get the four values used to clear the color buffers.
	/// </summary>
	/// <returns> the red, green, blue, and alpha values. </returns>
	GRAPHICSENGINE_API auto GetColorClearValue() -> std::optional<std::array<float, 4> >;

	/// <summary>
	/// Gets the error flag; if an error is indicated, logs the error.
	/// </summary>
	/// <param name="file"> Use __FILE__ for logging purposes. </param>
	/// <param name="function"> Use __func__, __FUNCTION__, or __PRETTY_FUNCTION__ for logging purposes. </param>
	/// <param name="line"> Use __LINE__ for logging purposes. </param>
	/// <returns> The error flag. </returns>
	GRAPHICSENGINE_API auto GetError(const char* file, const char* function, int line) -> ErrorFlag;

	/// <summary>
	/// Check a shader's delete status.
	/// </summary>
	/// <param name="shader"> Specifies the shader object to be queried. </param>
	/// <returns> true if shader is currently flagged for deletion; false if shader is 
	///           currently not flagged for deletion; nullopt if an error occurred while 
	///           querying the shader object. </returns>
	GRAPHICSENGINE_API auto GetShaderDeleteStatus(GLuint shader) -> std::optional<bool>;

	/// <summary>
	/// Links a program object.
	/// </summary>
	/// <param name="program"> Speifies the handle of the program object to be linked. </param>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto LinkProgram(GLuint program) -> bool;

	/// <summary>
	/// Select a polygon rasterization mode.
	/// </summary>
	/// <param name="mode"> Specifies how polygons will be rasterized. </param>
	/// <returns> true if it succeeded; false otherwise </returns>
	GRAPHICSENGINE_API auto PolygonMode(PolygonModeType mode) -> bool;

	/// <summary>
	/// Replaces the source code in a shader object.
	/// </summary>
	/// <param name="shader"> Specifies the handle of the shader object whose source code is to be replaced. </param>
	/// <param name="sources"> A vector of strings containing the source code to be loaded into the shader. </param>
	/// <returns> true if it succeeded; false otherwise </returns>
	GRAPHICSENGINE_API auto ShaderSource(GLuint shader, const std::vector<std::string>& sources) -> bool;

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

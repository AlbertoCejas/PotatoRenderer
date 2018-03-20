#ifndef _GL_ENUMS_H_
#define _GL_ENUMS_H_

#include <GL/glew.h>
#include <cinttypes>

enum class ShaderType : int32_t
{
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

enum class ShaderProgramParamName : int32_t
{
	ACTIVE_ATTRIBUTES = GL_ACTIVE_ATTRIBUTES,
	ACTIVE_UNIFORMS = GL_ACTIVE_UNIFORMS
};

enum class DrawMode : int32_t
{
	POINTS = GL_POINTS,
	LINES = GL_LINES,
	FILLED = GL_TRIANGLES
};

enum class TextureParameter : int32_t
{
	WRAP_S = GL_TEXTURE_WRAP_S,
	WRAP_T = GL_TEXTURE_WRAP_T,
	MIN_FILTER = GL_TEXTURE_MIN_FILTER,
	MAG_FILTER = GL_TEXTURE_MAG_FILTER
};

enum class TextureFilter : int32_t
{
	LINEAR = GL_LINEAR,
	NEAREST = GL_NEAREST
};

enum class TextureWrap : int32_t
{
	REPEAT = GL_REPEAT,
	MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
	CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
	CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
};

enum class TextureUnit : int32_t
{
	TEXTURE_UNIT_0 = GL_TEXTURE0,
	TEXTURE_UNIT_1 = GL_TEXTURE1,
	TEXTURE_UNIT_2 = GL_TEXTURE2,
	TEXTURE_UNIT_3 = GL_TEXTURE3,
	TEXTURE_UNIT_4 = GL_TEXTURE4,
	TEXTURE_UNIT_5 = GL_TEXTURE5,
	TEXTURE_UNIT_6 = GL_TEXTURE6,
	TEXTURE_UNIT_7 = GL_TEXTURE7,
	TEXTURE_UNIT_8 = GL_TEXTURE8,
	TEXTURE_UNIT_9 = GL_TEXTURE9,
	TEXTURE_UNIT_10 = GL_TEXTURE10,
	TEXTURE_UNIT_11 = GL_TEXTURE11,
	TEXTURE_UNIT_12 = GL_TEXTURE12,
	TEXTURE_UNIT_13 = GL_TEXTURE13,
	TEXTURE_UNIT_14 = GL_TEXTURE14,
	TEXTURE_UNIT_15 = GL_TEXTURE15
};

#endif
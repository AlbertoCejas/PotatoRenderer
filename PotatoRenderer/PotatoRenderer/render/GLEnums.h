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

#endif
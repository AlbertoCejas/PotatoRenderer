#include "VAO.h"
#include <GL/glew.h>

VAO::VAO()
{
	glGenVertexArrays(1, &vaoId);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &vaoId);
}

void VAO::bind()
{
	glBindVertexArray(vaoId);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}
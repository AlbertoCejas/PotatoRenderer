#include "IBOSubData.h"
#include <GL/glew.h>

IBOSubData::IBOSubData(bool _isStatic, int _maxIndices) : maxNumOfIndices(_maxIndices), currentNumOfIndices(0), isStatic(_isStatic)
{
	indices = new int32_t[_maxIndices];

	glGenBuffers(1, &IBOhandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOhandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _maxIndices, indices, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IBOSubData::~IBOSubData()
{
	glDeleteBuffers(1, &IBOhandle);
	delete[] indices;
}
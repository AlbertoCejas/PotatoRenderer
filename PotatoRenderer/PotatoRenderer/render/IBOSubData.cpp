#include "IBOSubData.h"
#include <GL/glew.h>
#include <cstring>
#include <cassert>

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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOhandle);
	glDeleteBuffers(1, &IBOhandle);
	delete[] indices;
}

void IBOSubData::bufferChanged()
{
	if (isBound)
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, currentNumOfIndices, indices);
		isDirty = false;
	}
}

void IBOSubData::setIndices(const int* indicesToSet, int count)
{
	assert(count >= 0 && count <= maxNumOfIndices);

	isDirty = true;
	currentNumOfIndices = count;

	memcpy(indices, indicesToSet, sizeof(int) * count);

	bufferChanged();
}

void IBOSubData::addIndices(const int* indicesToAdd, int count)
{
	assert(count > 0 && (currentNumOfIndices + count) <= maxNumOfIndices);

	isDirty = true;

	memcpy(indices + currentNumOfIndices, indicesToAdd, sizeof(int) * count);
	currentNumOfIndices += count;

	bufferChanged();
}

void IBOSubData::updateIndices(const int* indicesToUpdate, int offset, int count)
{
	assert(count > 0 && offset > -1 && ((offset + count) < maxNumOfIndices));

	isDirty = true;

	memcpy(indices + offset, indicesToUpdate, sizeof(int) * count);

	bufferChanged();
}

void IBOSubData::setNumOfIndices(int numOfIndices)
{
	assert(numOfIndices >= 0 && numOfIndices <= maxNumOfIndices);

	currentNumOfIndices = numOfIndices;

	isDirty = true;

	bufferChanged();
}

void IBOSubData::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOhandle);
	if (isDirty) 
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, currentNumOfIndices, indices);
		isDirty = false;
	}
	isBound = true;
}

void IBOSubData::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	isBound = false;
}
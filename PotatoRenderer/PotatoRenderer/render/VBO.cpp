#include "VBO.h"
#include <GL/glew.h>
#include "render/VertexAttribute.h"

VBO::VBO(bool isStatic, int numVertices, const std::vector<VertexAttribute>& vertexAttributesArray) :
	vertices(nullptr), 
	vertexAttributes(VertexAttributes(vertexAttributesArray)),
	isStatic(isStatic), 
	isBound(false), 
	isDirty(false)
{
	verticesSize = vertexAttributes.vertexSize() * numVertices / 4;
	vertices = new float[verticesSize];
	currentNumOfVertices = 0;

	glGenBuffers(1, &vboId);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &vboId);
}

void VBO::bind(ShaderProgram& shaderProgram)
{

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	
	if (isDirty)
	{
		glBufferData(GL_ARRAY_BUFFER, currentNumOfVertices * vertexAttributes.vertexSize(), vertices, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
		isDirty = false;
	}
	
	defineAttributes(shaderProgram);
	isBound = true;
}

void VBO::defineAttributes(ShaderProgram& shaderProgram)
{
	for (unsigned int i = 0u; i < vertexAttributes.size(); i++)
	{
		VertexAttribute& vertexAttribute = vertexAttributes.get(i);
		shaderProgram.setVertexAttribute
		(
			vertexAttribute.getLocation(),
			vertexAttribute.getNumOfComponents(),
			vertexAttribute.getType(),
			vertexAttribute.isNormalized(),
			vertexAttributes.vertexSize(),
			vertexAttribute.getOffset()
		);
			
		shaderProgram.enableVertexAttribute(vertexAttribute.getLocation());
	}
}

void VBO::unbind(ShaderProgram& shader, int* locations)
{
	unsigned int numAttributes = vertexAttributes.size();
	if (locations == nullptr)
	{
		for (unsigned int i = 0u; i < numAttributes; i++)
		{
			shader.disableVertexAttribute(vertexAttributes.get(i).getAlias());
		}
	}
	else {
		for (unsigned int i = 0u; i < numAttributes; i++)
		{
			int location = locations[i];
			if (location >= 0)
				shader.disableVertexAttribute(location);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	isBound = false;
}

void VBO::setVertices(float* verticesToSet, int numOfVerticesToSet)
{
	isDirty = true;
	currentNumOfVertices = numOfVerticesToSet;

	int numOfFloatsToCopy = currentNumOfVertices * vertexAttributes.vertexSize();
	for (int i = 0; i < numOfFloatsToCopy; i++)
	{
		this->vertices[i] = verticesToSet[i];
	}
	glBufferData(GL_ARRAY_BUFFER, numOfVerticesToSet, verticesToSet, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

void VBO::bufferChanged()
{
	if (isBound)
	{
		glBufferData(GL_ARRAY_BUFFER, currentNumOfVertices * vertexAttributes.vertexSize(), vertices, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
		isDirty = false;
	}
}

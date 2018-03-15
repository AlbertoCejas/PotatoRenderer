#include "Mesh.h"

Mesh::Mesh(bool isStatic, int maxVertices, const std::vector<VertexAttribute>& attributes) : vertexData(isStatic, maxVertices, attributes)
{

}

Mesh::~Mesh()
{

}

Mesh& Mesh::setVertices(float* vertices, int numOfVertices)
{
	vertexData.setVertices(vertices, numOfVertices);
	return *this;
}

Mesh& Mesh::addVertices(float* vertices, int numOfVertices)
{
	vertexData.addVertices(vertices, numOfVertices);
	return *this;
}

Mesh& Mesh::updateVertices(float* vertices, int numOfVerticesOffset, int numOfVertices)
{
	vertexData.updateVertices(vertices, numOfVerticesOffset, numOfVertices);
	return *this;
}

bool Mesh::hasVertexAttribute(VertexAttribute::Usage usage) // TODO: const here
{
	VertexAttributes& attributes = vertexData.getAttributes();
	unsigned int len = attributes.numOfAttributes();

	for (unsigned int i = 0u; i < len; i++)
	{
		if (attributes.get(i).getUsage() == usage)
		{
			return true;
		}
	}

	return false;
}

VertexAttribute* Mesh::getVertexAttribute(VertexAttribute::Usage usage) // TODO: const here
{
	VertexAttributes& attributes = vertexData.getAttributes();
	unsigned int len = attributes.numOfAttributes();

	for (unsigned int i = 0u; i < len; i++)
	{
		VertexAttribute& vertexAttribute = attributes.get(i);

		if (vertexAttribute.getUsage() == usage)
		{
			return &vertexAttribute;
		}
	}

	return nullptr;
}

void Mesh::bind(ShaderProgram& shader)
{
	vertexData.bind(shader);
}

void Mesh::unbind()
{
	vertexData.unbind();
}

void Mesh::render(ShaderProgram& shader)
{
	render(shader, GL_TRIANGLES);
}

void Mesh::render(ShaderProgram& shader, int primitiveType)
{
	int numVertices = getNumVertices();
	render(shader, 0, numVertices, primitiveType);
}

void Mesh::render(ShaderProgram& shader, int offset, int count, int primitiveType)
{
	if (count == 0)
	{
		return;
	}

	bind(shader);
	glDrawArrays(primitiveType, offset, count);
	unbind();
}
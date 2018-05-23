#include "Mesh.h"

Mesh::Mesh(bool isStatic, int maxVertices, int maxIndices, const std::vector<VertexAttribute>& attributes) : vertexData(isStatic, maxVertices, attributes), indexData(isStatic, maxIndices)
{

}

Mesh::~Mesh()
{

}

Mesh& Mesh::setVertices(const float* vertices, int numOfVertices)
{
	vertexData.setVertices(vertices, numOfVertices);
	return *this;
}

Mesh& Mesh::addVertices(const float* vertices, int numOfVertices)
{
	vertexData.addVertices(vertices, numOfVertices);
	return *this;
}

Mesh& Mesh::updateVertices(const float* vertices, int numOfVerticesOffset, int numOfVertices)
{
	vertexData.updateVertices(vertices, numOfVerticesOffset, numOfVertices);
	return *this;
}

Mesh& Mesh::setIndices(const int* indices, int numOfIndices)
{
	indexData.setIndices(indices, numOfIndices);
}

Mesh& Mesh::addIndices(const int* indices, int numOfIndices)
{
	indexData.addIndices(indices, numOfIndices);
}

Mesh& Mesh::updateIndices(const int* indices, int numOfIndicesOffset, int numOfIndices)
{
	indexData.updateIndices(indices, numOfIndicesOffset, numOfIndices);
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
	if (indexData.getNumOfIndices() > 0) indexData.bind();
}

void Mesh::unbind()
{
	vertexData.unbind();
	if (indexData.getNumOfIndices() > 0) indexData.unbind();
}

void Mesh::render(ShaderProgram& shader)
{
	render(shader, GL_TRIANGLES);
}

void Mesh::render(ShaderProgram& shader, int primitiveType)
{
	int numVertices = getNumVertices();
	render(shader, 0, indexData.getMaxNumOfIndices() > 0 ? getNumIndices() : getNumVertices(), primitiveType);
}

void Mesh::render(ShaderProgram& shader, int offset, int count, int primitiveType)
{
	if (count == 0)
	{
		return;
	}

	bind(shader);

	if (indexData.getNumOfIndices() > 0)
	{
		glDrawElements(primitiveType, count, GL_UNSIGNED_SHORT, indexData.getIndices());
	}
	else
	{
		glDrawArrays(primitiveType, offset, count);
	}

	unbind();
}
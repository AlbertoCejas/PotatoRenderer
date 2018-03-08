#include "VBOwithVAO.h"
#include "render/ShaderProgram.h"

VBOWithVAO::VBOWithVAO(bool isStatic, int numVertices, const std::vector<VertexAttribute>& attributes) :
	currentNumOfVertices(0),
	maxNumOfVertices(numVertices),
	vertices(nullptr),
	vertexAttributes(attributes),
	isStatic(isStatic),
	isBound(false),
	isDirty(false)
{
	verticesSize = vertexAttributes.getVertexSize() * numVertices / 4;
	vertices = new float[verticesSize];

	glGenBuffers(1, &VBOhandle);
	glGenVertexArrays(1, &VAOhandle);

}

VBOWithVAO::~VBOWithVAO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBOhandle);
	delete[] vertices;
	glDeleteVertexArrays(1, &VAOhandle);
}

void VBOWithVAO::bufferChanged()
{
	if (isBound)
	{
		glBufferData(GL_ARRAY_BUFFER, currentNumOfVertices * vertexAttributes.getVertexSize(), vertices, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
		isDirty = false;
	}
}

void VBOWithVAO::setVertices(float* verticesToSet, int numOfVerticesToSet)
{
	isDirty = true;
	currentNumOfVertices = numOfVerticesToSet;

	int numOfFloatsToCopy = currentNumOfVertices * vertexAttributes.getVertexSize();

	for (int i = 0; i < numOfFloatsToCopy; i++)
	{
		this->vertices[i] = verticesToSet[i];
	}

	bufferChanged();
}

void VBOWithVAO::bind(ShaderProgram& shaderProgram)
{
	bind(shaderProgram, nullptr, 0);
}

void VBOWithVAO::bind(ShaderProgram& shaderProgram, int* locations, int numOfLocations)
{
	glBindVertexArray(VAOhandle);

	bindAttributes(shaderProgram, locations, numOfLocations);

	bindData(); // Only if changed

	isBound = true;
}

void VBOWithVAO::bindAttributes(ShaderProgram& shaderProgram, int* locations, int numOfLocations)
{
	bool stillValid = !cachedLocations.empty();
	unsigned int numAttributes = vertexAttributes.size();

	if (stillValid)
	{
		if (locations == nullptr)
		{
			for (unsigned int i = 0u; stillValid && i < numAttributes; i++)
			{
				VertexAttribute& attribute = vertexAttributes.get(i);
				int location = shaderProgram.fetchAttributeLocation(attribute.getAlias());
				stillValid = location == cachedLocations.at(i);
			}
		}
		else
		{
			stillValid = (((unsigned int)numOfLocations) == cachedLocations.size());

			for (unsigned int i = 0u; stillValid && i < numAttributes; i++)
			{
				stillValid = locations[i] == cachedLocations.at(i);
			}
		}
	}

	if (!stillValid)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBOhandle);
		unbindAttributes(shaderProgram);
		cachedLocations.clear();

		for (unsigned int i = 0u; i < numAttributes; i++)
		{
			VertexAttribute& vertexAttribute = vertexAttributes.get(i);

			if (locations == nullptr)
			{
				cachedLocations.push_back(shaderProgram.fetchAttributeLocation(vertexAttribute.getAlias()));
			}
			else
			{
				cachedLocations.push_back(locations[i]);
			}

			int location = cachedLocations.at(i);

			if (location < 0)
			{
				continue;
			}

			shaderProgram.enableVertexAttribute(location);
			shaderProgram.setVertexAttribute
			(
			    location,
			    vertexAttribute.getNumOfComponents(),
			    vertexAttribute.getType(),
			    vertexAttribute.isNormalized(),
			    vertexAttributes.getVertexSize(),
			    vertexAttribute.getOffset()
			);
		}
	}
}

void VBOWithVAO::unbindAttributes(ShaderProgram& shaderProgram)
{
	if (cachedLocations.empty())
	{
		return;
	}

	unsigned int numAttributes = vertexAttributes.size();

	for (unsigned int i = 0u; i < numAttributes; i++)
	{
		int location = cachedLocations.at(i);

		if (location < 0)
		{
			continue;
		}

		shaderProgram.disableVertexAttribute(location);
	}
}


void VBOWithVAO::bindData()
{
	if (isDirty)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBOhandle);
		glBufferData(GL_ARRAY_BUFFER, currentNumOfVertices * vertexAttributes.getVertexSize(), vertices, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
		isDirty = false;
	}
}

void VBOWithVAO::unbind()
{
	glBindVertexArray(0);
	isBound = false;
}
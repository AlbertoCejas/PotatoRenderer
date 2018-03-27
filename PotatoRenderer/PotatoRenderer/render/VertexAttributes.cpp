#include "VertexAttributes.h"

VertexAttributes::VertexAttributes(const std::vector<VertexAttribute>& attributesToSet) : attributes(attributesToSet)
{
	vertexSizeBytes = calculateOffsets();
}

int VertexAttributes::calculateOffsets()
{
	int count = 0;

	for (unsigned int i = 0u; i < attributes.size(); i++)
	{
		VertexAttribute& attribute = attributes.at(i);
		attribute.setOffset(count);

		if (attribute.getType() == GL_FLOAT) // TODO: MAP THIS
		{
			count += (4 * attribute.getNumOfComponents());
		}
		else if (attribute.getType() == GL_UNSIGNED_BYTE)
		{
			count += attribute.getNumOfComponents();
		}
	}

	return count;
}
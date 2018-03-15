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

		count += (4 * attribute.getNumOfComponents());
	}

	return count;
}
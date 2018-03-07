#include "VertexAttributes.h"

VertexAttributes::VertexAttributes(const std::vector<VertexAttribute>& attributes)
{
	m_attributes = std::vector<VertexAttribute>(attributes);
	m_vertexSize = calculateOffsets();
}

int VertexAttributes::calculateOffsets()
{
	int count = 0;

	for (unsigned int i = 0u; i < m_attributes.size(); i++)
	{
		VertexAttribute& attribute = m_attributes.at(i);
		attribute.setOffset(count);

		count += (4 * attribute.getNumOfComponents());
	}

	return count;
}
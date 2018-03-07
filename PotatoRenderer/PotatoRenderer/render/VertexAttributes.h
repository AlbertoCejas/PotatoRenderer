#ifndef _VERTEX_ATTRIBUTES_H_
#define _VERTEX_ATTRIBUTES_H_

#include "VertexAttribute.h"
#include <vector>
#include <cinttypes>

class VertexAttributes
{
  public:

	explicit VertexAttributes(const std::vector<VertexAttribute>& attributes);

	inline int vertexSize() const { return m_vertexSize; }
	inline unsigned int numOfAttributes() const { return m_attributes.size(); }
	inline VertexAttribute& get(unsigned int index) { return m_attributes[index]; }
	inline unsigned int size() const { return m_attributes.size(); }

  private:

	int calculateOffsets();

	int32_t m_vertexSize;
	std::vector<VertexAttribute> m_attributes;
};

#endif
#ifndef _VERTEX_ATTRIBUTES_H_
#define _VERTEX_ATTRIBUTES_H_

#include "VertexAttribute.h"
#include <vector>
#include <cinttypes>

class VertexAttributes
{
  public:

	explicit VertexAttributes(const std::vector<VertexAttribute>& attributes);

	inline int getVertexSize() const { return vertexSize; }
	inline unsigned int numOfAttributes() const { return attributes.size(); }
	inline VertexAttribute& get(unsigned int index) { return attributes[index]; }
	inline unsigned int size() const { return attributes.size(); }

  private:

	int calculateOffsets();

	int32_t vertexSize;
	std::vector<VertexAttribute> attributes;
};

#endif
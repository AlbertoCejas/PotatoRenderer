#ifndef _VBO_H_
#define _VBO_H_

#include <cinttypes>
#include <vector>
#include "render/VertexAttributes.h"

class ShaderProgram;
class VertexAttribute;

class VBO
{
  public:

	VBO(bool isStatic, int numVertices, const std::vector<VertexAttribute>& attributes);
	~VBO();

	inline const VertexAttributes& getAttributes() const { return vertexAttributes; }
	inline VertexAttributes& getAttributes() { return vertexAttributes; }
	inline int getNumVertices() const  { return currentNumOfVertices; };

	void bind(ShaderProgram& shaderProgram);
	void unbind(ShaderProgram& shader, int* locations);

	void setVertices(float* vertices, int verticesSize);

  private:

	void defineAttributes(ShaderProgram& shaderProgram);
	void bufferChanged();

	uint32_t                            vboId;
	int32_t                             currentNumOfVertices;
	int32_t                             verticesSize;
	float*                              vertices;
	VertexAttributes                    vertexAttributes;
	bool                                isStatic;
	bool                                isBound;
	bool                                isDirty;

};

#endif
#ifndef _VBO_WITH_VAO_H_
#define _VBO_WITH_VAO_H_

#include "render/VertexAttributes.h"
#include <vector>

class ShaderProgram;

class VBOWithVAO
{
  public:

	VBOWithVAO(bool isStatic, int numVertices, const std::vector<VertexAttribute>& attributes);
	~VBOWithVAO();

	inline VertexAttributes& getAttributes() { return vertexAttributes; }
	inline int getMaxNumVertices() const { return maxNumOfVertices; }
	inline int getCurrentNumVertices() const { return currentNumOfVertices; };
	inline int getVertexSize() const { return verticesSize / maxNumOfVertices; }
	inline const float* getVertices() const { return vertices; }
	inline float* getVertices() { isDirty = true; return vertices; }

	void setVertices(const float* vertices, int numOfVertices);
	void addVertices(const float* vertices, int numOfVertices);
	void updateVertices(const float* vertices, int numOfVerticesOffset, int numOfVertices);

	void bind(ShaderProgram& shaderProgram);
	void bind(ShaderProgram& shaderProgram, int* locations, int numOfLocations);
	void unbind();

  private:

	void bufferChanged();
	void bindAttributes(ShaderProgram& shaderProgram, int* locations, int numOfLocations);
	void unbindAttributes(ShaderProgram& shaderProgram);
	void bindData();


	std::vector<int>                    cachedLocations;
	uint32_t                            VBOhandle;
	uint32_t                            VAOhandle;
	int32_t                             currentNumOfVertices;
	int32_t                             maxNumOfVertices;
	int32_t                             verticesSize;
	float*                              vertices;
	VertexAttributes                    vertexAttributes;
	bool                                isStatic;
	bool                                isBound;
	bool                                isDirty;
};


#endif // _VBO_WITH_VAO_H_
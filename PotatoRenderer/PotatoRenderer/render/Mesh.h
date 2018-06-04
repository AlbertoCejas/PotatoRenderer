#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include "render/VBOwithVAO.h"
#include "render/IBOSubData.h"
#include "render/VertexAttribute.h"

class ShaderProgram;

class Mesh
{
  public:

	Mesh(bool isStatic, int maxVertices, int maxIndices, const std::vector<VertexAttribute>& attributes);
	~Mesh();

	Mesh& setVertices(const float* vertices, int numOfVertices);
	Mesh& addVertices(const float* vertices, int numOfVertices);
	Mesh& updateVertices(const float* vertices, int numOfVerticesOffset, int numOfVertices);

	Mesh& setNumOfIndices(int numOfIndices);
	Mesh& setIndices(const int* indices, int numOfIndices);
	Mesh& addIndices(const int* indices, int numOfIndices);
	Mesh& updateIndices(const int* indices, int numOfIndicesOffset, int numOfIndices);

	bool hasVertexAttribute(VertexAttribute::Usage usage);
	VertexAttribute* getVertexAttribute(VertexAttribute::Usage usage);
	VertexAttributes& getVertexAttributes() { return vertexData.getAttributes(); }

	inline int getMaxNumVertices() const { return vertexData.getMaxNumVertices(); }
	inline int getNumVertices() const { return vertexData.getCurrentNumVertices(); }

	inline int getMaxNumIndices() const { return indexData.getMaxNumOfIndices(); }
	inline int getNumIndices() const { return indexData.getNumOfIndices(); }

	void bind(ShaderProgram& shader);
	void unbind();

	void render(ShaderProgram& shader);
	void render(ShaderProgram& shader, int primitiveType);
	void render(ShaderProgram& shader, int offset, int count, int primitiveType);


  private:

	VBOWithVAO vertexData;
	IBOSubData indexData;

};

#endif
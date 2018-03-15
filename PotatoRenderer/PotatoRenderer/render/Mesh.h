#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include "render/VBOwithVAO.h"
#include "render/VertexAttribute.h"

class ShaderProgram;

class Mesh
{
  public:

	explicit Mesh(bool isStatic, int numVertices, const std::vector<VertexAttribute>& attributes);
	~Mesh();

	Mesh& setVertices(float* vertices, int numOfVertices);
	Mesh& addVertices(float* vertices, int numOfVertices);
	Mesh& updateVertices(float* vertices, int numOfVerticesOffset, int numOfVertices);

	bool hasVertexAttribute(VertexAttribute::Usage usage);
	VertexAttribute* getVertexAttribute(VertexAttribute::Usage usage);
	VertexAttributes& getVertexAttributes() { return vertexData.getAttributes(); }

	inline int getMaxNumVertices() const { return vertexData.getMaxNumVertices(); }
	inline int getNumVertices() const { return vertexData.getCurrentNumVertices(); }

	void bind(ShaderProgram& shader);
	void unbind();

	void render(ShaderProgram& shader);
	void render(ShaderProgram& shader, int primitiveType);
	void render(ShaderProgram& shader, int offset, int count, int primitiveType);


  private:

	VBOWithVAO vertexData;

};

#endif
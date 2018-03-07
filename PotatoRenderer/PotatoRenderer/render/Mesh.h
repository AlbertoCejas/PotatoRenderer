#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include "render/VAO.h"
#include "render/VBO.h"
#include "render/VertexAttribute.h"

class ShaderProgram;

class Mesh
{
  public:

	explicit Mesh(bool isStatic, int numVertices, const std::vector<VertexAttribute>& attributes);
	~Mesh();

	Mesh* setVertices(float* vertices, int currentNumOfVertices);

	bool hasVertexAttribute(VertexAttribute::Usage usage);
	VertexAttribute* getVertexAttribute(VertexAttribute::Usage usage);
	VertexAttributes& getVertexAttributes() { return vbo.getAttributes(); }
	const VertexAttributes& getVertexAttributes() const { return vbo.getAttributes(); }

	inline int getNumVertices() const { return vbo.getNumVertices(); }

	void bind(ShaderProgram& shader);
	void unbind(ShaderProgram& shader);
	void unbind(ShaderProgram& shader, int* locations);

	void render(ShaderProgram& shader, int primitiveType);
	void render(ShaderProgram& shader, int offset, int count, int primitiveType);


  private:

	VAO vao;
	VBO vbo;

};

#endif
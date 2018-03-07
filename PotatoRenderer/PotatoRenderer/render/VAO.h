#ifndef _VAO_H_
#define _VAO_H_

#include <cinttypes>

class VAO // VertexArrayObject
{
  public:

	explicit VAO();
	~VAO();

	void bind();
	void unbind();

  private:

	uint32_t vaoId;
};

#endif
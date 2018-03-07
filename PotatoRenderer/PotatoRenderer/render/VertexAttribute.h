#ifndef _VERTEX_ATTRIBUTE_H_
#define _VERTEX_ATTRIBUTE_H_

#include "ShaderProgram.h"
#include <cstdint>
#include <GL/glew.h>

class VertexAttribute
{
  public:

	enum class Usage : std::int32_t { POSITION, COLOR };

	static const Usage POSITION = Usage::POSITION;
	static const Usage COLOR = Usage::COLOR;

	static VertexAttribute* position() { return new VertexAttribute(POSITION, 3, ShaderProgram::POSITION_ATTRIBUTE); }
	static VertexAttribute* color() { return new VertexAttribute(COLOR, 3, GL_FLOAT, false, ShaderProgram::COLOR_ATTRIBUTE); }


	VertexAttribute(Usage usage, int numComponents, const char* alias) :
		VertexAttribute
		(
		    usage,
		    numComponents,
		    GL_FLOAT,
			false,
		    alias
		) {}

	inline int getLocation() const { return (int) usage; }
	inline Usage getUsage() const { return usage; }
	inline int getNumOfComponents() const { return numOfComponents; }
	inline bool isNormalized() const { return normalized; }
	inline int getType() const { return type; }
	inline int getOffset() const { return offset; }
	inline const char* getAlias() const { return alias; }

	inline void setOffset(int offsetToSet) { offset = offsetToSet; }

  private:

	VertexAttribute(Usage usage, int numComponents, int type, bool normalized, const char* alias)
		: usage(usage), numOfComponents(numComponents), type(type), alias(alias), normalized(normalized) {}

	Usage           usage;
	int32_t         numOfComponents;
	int32_t         type;
	int32_t         offset;
	const char*     alias;
	bool            normalized;
};

#endif // _VERTEX_ATTRIBUTE_H_

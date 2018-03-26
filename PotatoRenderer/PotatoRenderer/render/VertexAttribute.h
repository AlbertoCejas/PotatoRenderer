#ifndef _VERTEX_ATTRIBUTE_H_
#define _VERTEX_ATTRIBUTE_H_

#include "ShaderProgram.h"
#include <cstdint>
#include <GL/glew.h>
#include <string>

class VertexAttribute
{
  public:

	enum class Usage : std::int32_t { POSITION, COLOR, TEXTURE_COORDS};

	//static const Usage POSITION = Usage::POSITION;
	//static const Usage COLOR = Usage::COLOR;
	//static const Usage TEXTURE_COORDS = Usage::TEXTURE_COORDS;

	static VertexAttribute position() { return VertexAttribute(Usage::POSITION, 3, ShaderProgram::POSITION_ATTRIBUTE); }
	static VertexAttribute color() { return VertexAttribute(Usage::COLOR, 4, GL_FLOAT, false, ShaderProgram::COLOR_ATTRIBUTE, 0); }
	static VertexAttribute texCoords(int unit) { return VertexAttribute(Usage::TEXTURE_COORDS, 2, GL_FLOAT, false, (ShaderProgram::TEXCOORD_ATTRIBUTE + std::to_string(unit)).c_str(), unit); }

	VertexAttribute(const VertexAttribute& other) : VertexAttribute(other.usage, other.numOfComponents, other.type, other.normalized, other.alias, other.unit)
	{

	}
	~VertexAttribute() { delete[] alias; }

	inline int getLocation() const { return (int) usage; }
	inline Usage getUsage() const { return usage; }
	inline int getNumOfComponents() const { return numOfComponents; }
	inline bool isNormalized() const { return normalized; }
	inline int getType() const { return type; }
	inline int getOffset() const { return offset; }
	inline const char* getAlias() const { return alias; }

	inline void setOffset(int offsetToSet) { offset = offsetToSet; }

  private:

	VertexAttribute(Usage usage, int numComponents, const char* alias) :
		VertexAttribute
		(
		    usage,
		    numComponents,
		    alias,
		    0
		) {}

	VertexAttribute(Usage usage, int numComponents, const char* alias, int index) :
		VertexAttribute
		(
		    usage,
		    numComponents,
		    GL_FLOAT,
		    false,
		    alias,
		    index
		) {}

	VertexAttribute(Usage _usage, int _numComponents, int _type, bool _normalized, const char* _alias, int _index)
		: usage(_usage), numOfComponents(_numComponents), type(_type), normalized(_normalized), unit(_index)
	{
		size_t aliasLength = strlen(_alias);
		alias = new char[aliasLength + 1];
		strcpy_s(alias, aliasLength + 1, _alias);
	}

	Usage           usage;
	int32_t         numOfComponents;
	int32_t         type;
	int32_t         offset;
	char*           alias;
	int32_t         unit;
	bool            normalized;
};

#endif // _VERTEX_ATTRIBUTE_H_

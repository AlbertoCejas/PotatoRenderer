#ifndef _SHADER_PROGRAM_H_
#define _SHADER_PROGRAM_H_

#include <cinttypes>
#include <unordered_map>
#include "utils/CharUtils.h"
#include "math/Matrix.h"

enum class ShaderType;

class ShaderProgram
{
  public:

	static constexpr const char* POSITION_ATTRIBUTE = "a_position";
	static constexpr const char* COLOR_ATTRIBUTE = "a_color";
	static constexpr const char* NORMAL_ATTRIBUTE = "a_normal";
	static constexpr const char* TEXCOORD_ATTRIBUTE = "a_texCoord";

	explicit ShaderProgram(bool hasNormals, bool hasColors, int numOfTextCoords);
	explicit ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
	~ShaderProgram();

	void begin();
	void end();

	void fetchUniforms();
	void fetchAttributes();
	unsigned int fetchUniformLocation(const char* name);
	unsigned int fetchAttributeLocation(const char* name);

	void setVertexAttribute(unsigned int location, int size, int type, bool normalize, int stride, int offset);

	void enableVertexAttribute(unsigned int location);
	void disableVertexAttribute(const char* name);
	void disableVertexAttribute(unsigned int location);

	void setUniformi(const char* name, int value);
	void setUniformMatrix(const char* name, const Mat4f& matrix);
	void setUniformMatrix(const char* name, const Mat4f& matrix, bool transpose);
	void setUniformMatrix(int location, const Mat4f& matrix);
	void setUniformMatrix(int location, const Mat4f& matrix, bool transpose);

  private:

	static std::string createDefaultVertexShader(bool hasNormals, bool hasColors, int numOfTextCoords);
	static std::string createDefaultFragmentShader(bool hasNormals, bool hasColors, int numOfTextCoords);
	/*static const char* DEFAULT_VERTEX_SHADER_SOURCE;
	static const char* DEFAULT_FRAGMENT_SHADER_SOURCE;*/

	int createShader(ShaderType type, const char* source);
	void compileShader(unsigned int shader);
	unsigned int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
	void linkProgram(unsigned int shaderProgram);

	uint32_t handler;

	std::vector<const char*> m_uniformsNames;
	std::vector<const char*> m_attributesNames;
	std::unordered_map<const char*, unsigned  int, CharStrHasher, CharStrComparator> m_uniforms;
	std::unordered_map<const char*, unsigned int, CharStrHasher, CharStrComparator> m_attributes;
	std::unordered_map<const char*, int, CharStrHasher, CharStrComparator> m_uniformsTypes;
	std::unordered_map<const char*, int, CharStrHasher, CharStrComparator> m_attributesTypes;
	std::unordered_map<const char*, int, CharStrHasher, CharStrComparator> m_uniformsSizes;
	std::unordered_map<const char*, int, CharStrHasher, CharStrComparator> m_attributesSizes;

};

#endif
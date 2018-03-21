#include "ShaderProgram.h"
#include <GL/glew.h>
#include <cassert>
#include "render/GLEnums.h"
#include <string>
#include <cstdlib>
/*
const char* ShaderProgram::DEFAULT_VERTEX_SHADER_SOURCE =
    "#version 330 core\n"
    "layout (location = 0) in vec3 a_position;\n"
    "layout (location = 1) in vec3 a_color;\n"
    "uniform mat4 u_projTrans;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "gl_Position = u_projTrans * vec4(a_position, 1.0);\n"
    "ourColor = a_color;\n"
    "}\0";

const char* ShaderProgram::DEFAULT_FRAGMENT_SHADER_SOURCE =
    "#version 330 core\n"
    "in vec3 ourColor;\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(ourColor, 1.0f);\n"
    "}\n\0";
*/

std::string ShaderProgram::createDefaultVertexShader(bool hasNormals, bool hasColors, int numOfTexCoords)
{
	std::string vertexShader("#version 330 core\n");
	vertexShader += ("attribute vec3 " + std::string(ShaderProgram::POSITION_ATTRIBUTE) + ";\n"); // Position
	vertexShader += hasNormals ? ("attribute vec3 " + std::string(ShaderProgram::NORMAL_ATTRIBUTE) + ";\n") : ""; // Normal
	vertexShader += hasColors ? ("attribute vec3 " + std::string(ShaderProgram::COLOR_ATTRIBUTE) + ";\n") : ""; // Color

	for (int i = 0; i < numOfTexCoords; i++)
	{
		vertexShader += "attribute vec2 " + std::string(ShaderProgram::TEXCOORD_ATTRIBUTE) + std::to_string(i) + ";\n"; // TexCoords
	}

	vertexShader += "uniform mat4 u_projTrans;\n";
	vertexShader += (hasColors ? "varying vec3 v_col;\n" : "");

	for (int i = 0; i < numOfTexCoords; i++)
	{
		vertexShader += "varying vec2 v_tex" + std::to_string(i) + ";\n";
	}

	vertexShader += "void main() {\n";
	vertexShader += "   gl_Position = u_projTrans * vec4(" + std::string(ShaderProgram::POSITION_ATTRIBUTE) + ", 1.0);\n"
	                + (hasColors ? "   v_col = " + std::string(ShaderProgram::COLOR_ATTRIBUTE) + ";\n" : "");

	for (int i = 0; i < numOfTexCoords; i++)
	{
		std::string iStr = std::to_string(i);
		vertexShader += "   v_tex" + iStr + " = " + ShaderProgram::TEXCOORD_ATTRIBUTE + iStr + ";\n";
	}

	vertexShader += "   gl_PointSize = 1.0;\n";
	vertexShader += "}\n";

	return vertexShader;
}

std::string ShaderProgram::createDefaultFragmentShader(bool, bool hasColors, int numOfTextCoords)
{
	std::string fragmentShader("#version 330 core\n");

	fragmentShader += "#ifdef GL_ES\n";
	fragmentShader += "precision mediump float;\n";
	fragmentShader += "#endif\n";

	if (hasColors) { fragmentShader += "varying vec3 v_col;\n"; }

	for (int i = 0; i < numOfTextCoords; i++)
	{
		std::string iStr = std::to_string(i);
		fragmentShader += "varying vec2 v_tex" + iStr + ";\n";
		fragmentShader += "uniform sampler2D u_sampler" + iStr + ";\n";
	}

	fragmentShader += "void main() {\n";
	fragmentShader += "   gl_FragColor = ";
	fragmentShader += (hasColors ? "vec4(v_col, 1.0f)" : "vec4(1, 1, 1, 1)");

	if (numOfTextCoords > 0) { fragmentShader += " * "; }

	for (int i = 0; i < numOfTextCoords; i++)
	{
		std::string iStr = std::to_string(i);

		if (i == numOfTextCoords - 1)
		{
			fragmentShader += " texture2D(u_sampler" + iStr + ",  v_tex" + iStr + ")";
		}
		else
		{
			fragmentShader += " texture2D(u_sampler" + iStr + ",  v_tex" + iStr + ") *";
		}
	}

	fragmentShader += ";\n}";

	return fragmentShader;
}

ShaderProgram::ShaderProgram(bool hasNormals, bool hasColors, int numOfTextCoords) :
	ShaderProgram(createDefaultVertexShader(hasNormals, hasColors, numOfTextCoords).c_str(), createDefaultFragmentShader(hasNormals, hasColors, numOfTextCoords).c_str()) { }

ShaderProgram::ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	int vertexShader = createShader(ShaderType::VERTEX_SHADER, vertexShaderSource);
	int fragmentShader = createShader(ShaderType::FRAGMENT_SHADER, fragmentShaderSource);

	compileShader(vertexShader);
	compileShader(fragmentShader);

	this->handler = createShaderProgram(vertexShader, fragmentShader);
	linkProgram(this->handler);

	fetchAttributes();
	fetchUniforms();

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(handler);

	for (const char* name : m_uniformsNames)
	{
		delete[] name;
	}

	for (const char* name : m_attributesNames)
	{
		delete[] name;
	}
}

int ShaderProgram::createShader(ShaderType type, const char* source)
{
	int shaderId = glCreateShader((int) type);
	glShaderSource(shaderId, 1, &source, NULL);
	return shaderId;
}

void ShaderProgram::compileShader(unsigned int shader)
{
	int success;
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	assert(success != 0);
}

unsigned int ShaderProgram::createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	return shaderProgram;
}

void ShaderProgram::linkProgram(unsigned int shaderProgram)
{
	glLinkProgram(shaderProgram);
	// Check for compile time errors
	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	assert(success != 0);
}

void ShaderProgram::begin()
{
	glUseProgram(handler);
}

void ShaderProgram::end()
{
	glUseProgram(0);
}

void ShaderProgram::fetchUniforms()
{
	unsigned int numOfUniforms;

	glGetProgramiv(handler, (int) ShaderProgramParamName::ACTIVE_UNIFORMS, (GLint*) &numOfUniforms);

	m_uniformsNames.resize(numOfUniforms);

	for (unsigned int i = 0u; i < numOfUniforms; i++)
	{
		int param;
		GLenum type;
		char name[30];
		int nameLength;

		glGetActiveUniform(handler, i, 30, &nameLength, &param, &type, name);
		int location = glGetUniformLocation(handler, name);

		char* cachedName = new char[nameLength + 1];
		strcpy_s(cachedName, nameLength + 1, name);
		m_uniforms.insert(std::make_pair(cachedName, location));
		m_uniformsTypes.insert(std::make_pair(cachedName, type));
		m_uniformsSizes.insert(std::make_pair(cachedName, param));
		m_uniformsNames[i] = cachedName;
	}
}

void ShaderProgram::fetchAttributes()
{
	unsigned int numAttributes;

	glGetProgramiv(handler, (int)ShaderProgramParamName::ACTIVE_ATTRIBUTES, (GLint*) &numAttributes);

	m_attributesNames.resize(numAttributes);

	for (unsigned int i = 0u; i < numAttributes; i++)
	{
		int param;
		GLenum type;
		char name[30];
		int nameLength;

		glGetActiveAttrib(handler, i, 30, &nameLength, &param, &type, name);
		unsigned int location = glGetAttribLocation(handler, name);
		char* cachedName = new char[nameLength + 1];
		strcpy_s(cachedName, nameLength + 1, name);
		m_attributes.insert(std::make_pair(cachedName, location));
		m_attributesTypes.insert(std::make_pair(cachedName, type));
		m_attributesSizes.insert(std::make_pair(cachedName, param));
		m_attributesNames[i] = cachedName;
	}
}

unsigned int ShaderProgram::fetchUniformLocation(const char* name)
{
	// -2 == not yet cached
	// -1 == cached but not found
	unsigned int location;
	auto it = m_uniforms.find(name);
	location = (it == m_uniforms.end()) ? -2 : it->second;

	if (location == -2)
	{
		location = glGetUniformLocation(handler, name);
		assert(location != -1); // "no uniform with name '" + name + "' in shader"
		m_uniforms.insert(std::make_pair(name, location));
	}

	return location;
}

unsigned int ShaderProgram::fetchAttributeLocation(const char* name)
{
	// -2 == not yet cached
	// -1 == cached but not found
	int location;
	auto it = m_attributes.find(name);
	location = (it == m_attributes.end()) ? -2 : it->second;

	if (location == -2)
	{
		location = glGetAttribLocation(handler, name);
		assert(location != -1); // "no attribute with name '" + name + "' in shader"
		m_attributes.insert(std::make_pair(name, location));
	}

	return location;
}


void ShaderProgram::setVertexAttribute(unsigned int location, int size, int type, bool normalize, int stride, int offset)
{
	glVertexAttribPointer(location, size, type, (GLboolean) normalize, stride, (void*)offset);
}

void ShaderProgram::enableVertexAttribute(unsigned int location)
{
	glEnableVertexAttribArray(location);
}

void ShaderProgram::disableVertexAttribute(const char* name)
{
	unsigned int location = fetchAttributeLocation(name);

	if (location == -1)
	{
		return;
	}

	glDisableVertexAttribArray(location);
}

void ShaderProgram::disableVertexAttribute(unsigned int location)
{
	glDisableVertexAttribArray(location);
}

void ShaderProgram::setUniformi(const char* name, int value)
{
	int location = fetchUniformLocation(name);
	glUniform1i(location, value);
}

void ShaderProgram::setUniformMatrix(const char* name, const Mat4f& matrix)
{
	setUniformMatrix(name, matrix, false);
}

void ShaderProgram::setUniformMatrix(const char* name, const Mat4f& matrix, bool transpose)
{
	int location = fetchUniformLocation(name);
	setUniformMatrix(location, matrix, transpose);
}

void ShaderProgram::setUniformMatrix(int location, const Mat4f& matrix)
{
	setUniformMatrix(location, matrix, false);
}

void ShaderProgram::setUniformMatrix(int location, const Mat4f& matrix, bool transpose)
{
	glUniformMatrix4fv(location, 1, transpose, (const GLfloat*) matrix.getData());
}

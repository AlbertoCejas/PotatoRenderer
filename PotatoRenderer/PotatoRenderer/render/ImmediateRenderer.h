#ifndef _IMMEDIATE_RENDERER_H_
#define _IMMEDIATE_RENDERER_H_

#include "render/ShaderProgram.h"
#include "render/Mesh.h"
#include <vector>
#include "render/Color.h"

enum class DrawMode;
class Texture;

class ImmediateRenderer
{
  public:

	explicit ImmediateRenderer(int _maxVertices);
	~ImmediateRenderer();

	void begin(const Mat4f& _transform, const DrawMode& drawMode);
	void vertex(float x, float y, float z);
	void vertex(float x, float y, float z, float u, float v);
	void end();
	void flush();

	inline const Mat4f* getTransform() const { return transform; }
	inline DrawMode getDrawMode() const { return drawMode; }
	inline int getNumVertices() const { return mesh.getNumVertices(); }
	inline int getMaxNumVertices() const { return mesh.getMaxNumVertices(); }

	inline const Color& getColor() const { return color; }
	void setColor(const Color& color);
	void setColor(float red, float green, float blue, float alpha);

	void setTextCoords(float u, float v);

	inline void setTexture(const Texture& _texture) { texture = &_texture; }
	inline void setDrawMode(DrawMode _drawMode) { drawMode = _drawMode; }

  private:

	static std::vector<VertexAttribute> buildVertexAttributes();

	void positionToVertexCache(float x, float y, float z);
	void colorToVertexCache(const Color& color);
	void textCoordsToVertexCache(float u, float v);

	int32_t maxVertices;
	int32_t numVertices;
	Mesh mesh;
	ShaderProgram shader;
	const Mat4f* transform;
	DrawMode drawMode;
	Color color;
	const Texture* texture;
	float* vertexCache;
};

#endif // _IMMEDIATE_RENDERER_H_
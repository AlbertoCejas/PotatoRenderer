#ifndef _SHAPE_RENDERER_H_
#define _SHAPE_RENDERER_H_

#include <cinttypes>
#include "GLEnums.h"
#include "math/Matrix.h"
#include "render/Color.h"
#include "render/ImmediateRenderer.h"

class ShapeRenderer
{
  public:

	explicit ShapeRenderer() : ShapeRenderer(5000) { }
	explicit ShapeRenderer(int maxVertices);

	void begin(const Mat4f& transformation, const DrawMode& type);

	void setColor(const Color& color);
	void setColor(float red, float green, float blue, float alpha);

	void point(float x, float y, float z);
	void point(float x, float y, float z, const Color& color);
	
	void line(float x1, float y1, float z1, float x2, float y2, float z2);
	void line(float x1, float y1, float z1, float x2, float y2, float z2, const Color& color);
	void line(float x1, float y1, float z1, float x2, float y2, float z2, const Color& col1, const Color& col2);
	
	void triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
	void triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, const Color& color);
	void triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, const Color& col1, const Color& col2, const Color& col3);

	// points must be adjacents
	void rectangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4);
	void rectangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, const Color& color);
	void rectangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, const Color& col1, const Color& col2, const Color& col3, const Color& col4);

	void circle(float x, float y, float z, float radius);
	void circle(float x, float y, float z, float radius, const Color& color);
	void circle(float x, float y, float z, float radius, int segments);
	void circle(float x, float y, float z, float radius, int segments, const Color& color);

	void end();

  private:

	void check(DrawMode preferred, DrawMode other, int newVertices);

	ImmediateRenderer immediateRenderer;
	Color color;
	bool alreadyBegun;
};

#endif
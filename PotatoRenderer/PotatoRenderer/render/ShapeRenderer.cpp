#include "render/ShapeRenderer.h"
#include "math/MathUtils.h"
#include "render/BaseCamera.h"
#include "math/Matrix.h"
#include <algorithm>
#include <cassert>

ShapeRenderer::ShapeRenderer(int maxVertices) : immediateRenderer(maxVertices), color(Color::BLACK), alreadyBegun(false)
{

}

void ShapeRenderer::begin(const BaseCamera& camera, const DrawMode& type)
{
	assert(!alreadyBegun);
	alreadyBegun = true;
	immediateRenderer.begin(camera.getCombined(), type);
}

void ShapeRenderer::setColor(const Color& _color)
{
	color.set(_color);
	immediateRenderer.setColor(_color);
}

void ShapeRenderer::setColor(float red, float green, float blue, float alpha)
{
	color.set(red, green, blue, alpha);
	immediateRenderer.setColor(red, green, blue, alpha);
}

void ShapeRenderer::point(float x, float y, float z)
{
	point(x, y, z, color);
}

void ShapeRenderer::point(float x, float y, float z, const Color& _color)
{
	immediateRenderer.setColor(_color);
	immediateRenderer.vertex(x, y, z);
}

void ShapeRenderer::line(float x1, float y1, float z1, float x2, float y2, float z2)
{
	line(x1, y1, z1, x2, y2, z2, color, color);
}

void ShapeRenderer::line(float x1, float y1, float z1, float x2, float y2, float z2, const Color& _color)
{
	line(x1, y1, z1, x2, y2, z2, _color, _color);
}

void ShapeRenderer::line(float x1, float y1, float z1, float x2, float y2, float z2, const Color& col1, const Color& col2)
{
	immediateRenderer.setColor(col1);
	immediateRenderer.vertex(x1, y1, z1);
	immediateRenderer.setColor(col2);
	immediateRenderer.vertex(x2, y2, z2);
}

void ShapeRenderer::triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
	triangle(x1, y1, z1, x2, y2, z2, x3, y3, z3, color, color, color);
}

void ShapeRenderer::triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, const Color& _color)
{
	triangle(x1, y1, z1, x2, y2, z2, x3, y3, z3, _color, _color, _color);
}

void ShapeRenderer::triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, const Color& col1, const Color& col2, const Color& col3)
{
	DrawMode drawMode = immediateRenderer.getDrawMode();

	immediateRenderer.setColor(col1);
	immediateRenderer.vertex(x1, y1, z1);
	immediateRenderer.setColor(col2);
	immediateRenderer.vertex(x2, y2, z2);

	if (drawMode == DrawMode::LINES)
	{
		immediateRenderer.setColor(col2);
		immediateRenderer.vertex(x2, y2, z2);
	}

	immediateRenderer.setColor(col3);
	immediateRenderer.vertex(x3, y3, z3);

	if (drawMode == DrawMode::LINES)
	{
		immediateRenderer.setColor(col3);
		immediateRenderer.vertex(x3, y3, z3);
		immediateRenderer.setColor(col1);
		immediateRenderer.vertex(x1, y1, z1);
	}
}

void ShapeRenderer::rectangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{
	rectangle(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, color, color, color, color);
}

void ShapeRenderer::rectangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, const Color& _color)
{
	rectangle(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, _color, _color, _color, _color);
}

void ShapeRenderer::rectangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, const Color& col1,
                              const Color& col2, const Color& col3, const Color& col4)
{
	if (immediateRenderer.getDrawMode() == DrawMode::LINES)
	{
		immediateRenderer.setColor(col1);
		immediateRenderer.vertex(x1, y1, z1);
		immediateRenderer.setColor(col2);
		immediateRenderer.vertex(x2, y2, z2);

		immediateRenderer.setColor(col2);
		immediateRenderer.vertex(x2, y2, z2);
		immediateRenderer.setColor(col3);
		immediateRenderer.vertex(x3, y3, z3);

		immediateRenderer.setColor(col3);
		immediateRenderer.vertex(x3, y3, z3);
		immediateRenderer.setColor(col4);
		immediateRenderer.vertex(x4, y4, z4);

		immediateRenderer.setColor(col4);
		immediateRenderer.vertex(x4, y4, z4);
		immediateRenderer.setColor(col1);
		immediateRenderer.vertex(x1, y1, z1);
	}
	else
	{
		immediateRenderer.setColor(col1);
		immediateRenderer.vertex(x1, y1, z1);
		immediateRenderer.setColor(col2);
		immediateRenderer.vertex(x2, y2, z2);
		immediateRenderer.setColor(col3);
		immediateRenderer.vertex(x3, y3, z3);

		immediateRenderer.setColor(col4);
		immediateRenderer.vertex(x4, y4, z4);
		immediateRenderer.setColor(col3);
		immediateRenderer.vertex(x3, y3, z3);
		immediateRenderer.setColor(col1);
		immediateRenderer.vertex(x1, y1, z1);
	}

}

void ShapeRenderer::circle(float x, float y, float z, float radius)
{
	circle(x, y, z, radius, std::max(1, (int)(6 * (float)std::cbrt(radius))), color);
}

void ShapeRenderer::circle(float x, float y, float z, float radius, const Color& _color)
{
	circle(x, y, z, radius, std::max(1, (int)(6 * (float)std::cbrt(radius))), _color);
}

void ShapeRenderer::circle(float x, float y, float z, float radius, int segments)
{
	circle(x, y, z, radius, segments, color);
}

void ShapeRenderer::circle(float x, float y, float z, float radius, int segments, const Color& _color)
{
	assert(segments > -1);

	float angle = 2 * MathUtils::PI / segments;
	float cos = std::cos(angle);
	float sin = std::sin(angle);
	float cx = radius, cy = 0;

	if (immediateRenderer.getDrawMode() == DrawMode::LINES)
	{
		check(DrawMode::LINES, DrawMode::FILLED, segments * 2 + 2);

		for (int i = 0; i < segments; i++)
		{
			immediateRenderer.setColor(_color);
			immediateRenderer.vertex(x + cx, y + cy, z);

			float temp = cx;
			cx = cos * cx - sin * cy;
			cy = sin * temp + cos * cy;

			immediateRenderer.setColor(_color);
			immediateRenderer.vertex(x + cx, y + cy, z);
		}

		// Ensure the last segment is identical to the first.
		immediateRenderer.setColor(_color);
		immediateRenderer.vertex(x + cx, y + cy, z);
	}
	else
	{
		check(DrawMode::LINES, DrawMode::FILLED, segments * 3 + 3);

		segments--;

		for (int i = 0; i < segments; i++)
		{
			immediateRenderer.setColor(_color);
			immediateRenderer.vertex(x, y, z);
			immediateRenderer.setColor(_color);
			immediateRenderer.vertex(x + cx, y + cy, z);

			float temp = cx;
			cx = cos * cx - sin * cy;
			cy = sin * temp + cos * cy;

			immediateRenderer.setColor(_color);
			immediateRenderer.vertex(x + cx, y + cy, z);
		}

		// Ensure the last segment is identical to the first.
		immediateRenderer.setColor(_color);
		immediateRenderer.vertex(x, y, z);
		immediateRenderer.setColor(_color);
		immediateRenderer.vertex(x + cx, y + cy, z);
	}

	cx = radius;
	cy = 0;
	immediateRenderer.setColor(_color);
	immediateRenderer.vertex(x + cx, y + cy, z);
}

void ShapeRenderer::end()
{
	assert(alreadyBegun);
	immediateRenderer.end();
	alreadyBegun = false;
}

void ShapeRenderer::check(DrawMode preferred, DrawMode other, int newVertices)
{
	assert(alreadyBegun);

	DrawMode drawMode = immediateRenderer.getDrawMode();

	if (drawMode != preferred && drawMode != other)
	{
		const Mat4f* transformation = immediateRenderer.getTransform();
		end();
		alreadyBegun = true;
		immediateRenderer.begin(*transformation, preferred);
	}
	else if (immediateRenderer.getMaxNumVertices() - immediateRenderer.getNumVertices() < newVertices)
	{
		// Not enough space.
		DrawMode type = drawMode;
		const Mat4f* transformation = immediateRenderer.getTransform();
		end();
		alreadyBegun = true;
		immediateRenderer.begin(*transformation, type);
	}
}
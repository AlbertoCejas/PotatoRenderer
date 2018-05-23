#include "render/ImmediateRenderer.h"

std::vector<VertexAttribute> ImmediateRenderer::buildVertexAttributes()
{
	std::vector<VertexAttribute> attribs = std::vector<VertexAttribute>();
	attribs.push_back(VertexAttribute::position());
	attribs.push_back(VertexAttribute::color());
	return attribs;
}

ImmediateRenderer::ImmediateRenderer(int _maxVertices) : maxVertices(_maxVertices), numVertices(0), mesh(false, _maxVertices, 0, buildVertexAttributes()), shader(false, true, 0),
	transform(nullptr), color(Color::BLACK)
{
	vertexCache = new float[mesh.getVertexAttributes().getVertexSizeBytes() / 4];
}

ImmediateRenderer::~ImmediateRenderer()
{
	delete[] vertexCache;
}

void ImmediateRenderer::begin(const Mat4f& _transform, const DrawMode& _drawMode)
{
	transform = &_transform;
	drawMode = _drawMode;
	numVertices = 0;
}

void ImmediateRenderer::vertex(float x, float y, float z)
{
	positionToVertexCache(x, y, z);
	colorToVertexCache(color);

	mesh.addVertices(vertexCache, 1);
	numVertices++;
}

void ImmediateRenderer::end()
{
	flush();
}

void ImmediateRenderer::flush()
{
	if (numVertices != 0)
	{
		shader.begin();
		shader.setUniformMatrix("u_projTrans", *transform);
		mesh.render(shader, (int)drawMode);
		shader.end();
		numVertices = 0;

		mesh.setVertices(nullptr, 0);
	}
}

void ImmediateRenderer::setColor(const Color& _color)
{
	color.set(_color);
}

void ImmediateRenderer::setColor(float red, float green, float blue, float alpha)
{
	color.set(red, green, blue, alpha);
}

void ImmediateRenderer::positionToVertexCache(float x, float y, float z)
{
	vertexCache[0] = x;
	vertexCache[1] = y;
	vertexCache[2] = z;
}

void ImmediateRenderer::colorToVertexCache(const Color& _color)
{
	vertexCache[3] = Color::toFloatBits(_color.r, _color.g, _color.b, _color.a);
}
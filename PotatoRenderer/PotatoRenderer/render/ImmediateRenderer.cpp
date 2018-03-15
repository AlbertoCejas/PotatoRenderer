#include "render/ImmediateRenderer.h"

std::vector<VertexAttribute> ImmediateRenderer::buildVertexAttributes()
{
	std::vector<VertexAttribute> attribs = std::vector<VertexAttribute>();
	attribs.push_back(VertexAttribute(VertexAttribute::POSITION, 3, ShaderProgram::POSITION_ATTRIBUTE));
	attribs.push_back(VertexAttribute(VertexAttribute::COLOR, 4, ShaderProgram::COLOR_ATTRIBUTE));
	return attribs;
}

ImmediateRenderer::ImmediateRenderer(int _maxVertices) : maxVertices(_maxVertices), numVertices(0), mesh(false, _maxVertices, buildVertexAttributes()), transform(nullptr),
	color(Color::BLACK)
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
	vertexCache[3] = _color.r;
	vertexCache[4] = _color.g;
	vertexCache[5] = _color.b;
	vertexCache[6] = _color.a;
}
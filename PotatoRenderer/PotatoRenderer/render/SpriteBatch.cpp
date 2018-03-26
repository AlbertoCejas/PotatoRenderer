#include "render/SpriteBatch.h"
#include "render/BaseCamera.h"
#include "render/Texture.h"
#include <algorithm>

std::vector<VertexAttribute> SpriteBatch::buildVertexAttributes()
{
	std::vector<VertexAttribute> attribs = std::vector<VertexAttribute>();
	attribs.push_back(VertexAttribute::position());
	attribs.push_back(VertexAttribute::color());
	attribs.push_back(VertexAttribute::texCoords(0));
	return attribs;
}

SpriteBatch::SpriteBatch(int _maxVertices) : batchedSprites(), selectedShader(nullptr), mesh(false, _maxVertices,
	        buildVertexAttributes()), defaultShader(false, true, 1), hasBegun(false), camera(nullptr), lastTexture(nullptr)
{
	batchedSprites.reserve(_maxVertices / 6);
	selectedShader = &defaultShader;
}

void SpriteBatch::begin(const BaseCamera& _camera)
{
	assert(!hasBegun);
	hasBegun = true;
	camera = &_camera;
}

void SpriteBatch::render(Sprite& sprite)
{
	Texture& texture = sprite.getTextureRegion().getTexture();

	batchedSprites.push_back(&sprite);

	lastTexture = &texture;

	if (lastTexture != nullptr && lastTexture != &texture)
	{
		flush();
	}
}

void SpriteBatch::end()
{
	assert(hasBegun);
	flush();
	hasBegun = false;
	lastTexture = nullptr;
}

void SpriteBatch::flush()
{
	if (batchedSprites.empty() == false)
	{
		buildMeshFromBatchedSprites();

		lastTexture->bindTexture();
		unsigned int location = selectedShader->fetchAttributeLocation((std::string(ShaderProgram::TEXCOORD_ATTRIBUTE) + "0").c_str());
		glUniform1i(location, 0);

		selectedShader->begin();
		selectedShader->setUniformMatrix("u_projTrans", camera->getCombined());
		mesh.render(*selectedShader);
		selectedShader->end();

		batchedSprites.clear();

		mesh.setVertices(nullptr, 0);
	}
}

void SpriteBatch::buildMeshFromBatchedSprites()
{
	// std::sort(batchedSprites.begin(), batchedSprites.end(), textureComparable)

	for (size_t i = 0u; i < batchedSprites.size(); i++)
	{
		copySpriteToMesh(batchedSprites[i]);
	}
}

void SpriteBatch::copySpriteToMesh(const Sprite* sprite)
{
	mesh.addVertices(sprite->getVertices().data(), 6);
}
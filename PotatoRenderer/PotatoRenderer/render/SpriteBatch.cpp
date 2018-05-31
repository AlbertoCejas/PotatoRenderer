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

SpriteBatch::SpriteBatch(int _maxVertices) : batchedSprites(), selectedShader(nullptr), mesh(false, _maxVertices, 1000, buildVertexAttributes()), 
	defaultShader(false, true, 1), hasBegun(false), camera(nullptr), lastTexture(nullptr)
{
	batchedSprites.reserve(1000u);
	selectedShader = &defaultShader;

	int* indices = new int[1000];
	short j = 0;
	for (int i = 0; i < 1000; i += 6, j += 4)
	{
		indices[i] = j;
		indices[i + 1] = (j + 1);
		indices[i + 2] = (j + 2);
		indices[i + 3] = (j + 2);
		indices[i + 4] = (j + 3);
		indices[i + 5] = j;
	}
	mesh.setIndices(indices, 1000);

	//delete[] indices; // TODO: FREE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

	if (lastTexture != &texture)
	{
		lastTexture = &texture;
		flush();
	}

	lastTexture = &texture;

	batchedSprites.push_back(&sprite);
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
		glUniform1i(location, lastTexture->getTextureUnitIndex());

		selectedShader->begin();
		selectedShader->setUniformMatrix("u_projTrans", camera->getCombined());
		mesh.render(*selectedShader);
		selectedShader->end();

		batchedSprites.clear();

		mesh.setVertices(nullptr, 0);
		//mesh.setIndices(nullptr, 0);
		lastTexture->unbindTexture();
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
	mesh.addVertices(sprite->getVertices().data(), 4); // // 6 is num of vertices required to from a rectangle, TODO: optimize with indices (4 vertices)
	//mesh.addIndices(sprite->getIndices().data(), 6);
}
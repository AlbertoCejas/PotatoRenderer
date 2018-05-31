#ifndef _SPRITE_BATCH_H_
#define _SPRITE_BATCH_H_

#include <cinttypes>
#include "render/Mesh.h"
#include "render/ShaderProgram.h"
#include "render/Sprite.h"
#include <array>
#include <vector>

class BaseCamera;
class Texture;

// TODO: layer, sort in flush

class SpriteBatch
{
  public:

	explicit SpriteBatch(int maxVertices); // TODO : change max vertices for max sprites size

	inline void setShader(ShaderProgram& shader) { selectedShader = &shader; }

	void begin(const BaseCamera& camera);
	void render(Sprite& sprite);
	void end();

  private:

	//static constexpr int32_t MAX_NUM_OF_VERTICES = std::numeric_limits<int32_t>::max();
	//static constexpr int32_t MAX_BATCHED_SPRITES = MAX_NUM_OF_VERTICES / Sprite::SPRITE_SIZE;

	static std::vector<VertexAttribute> buildVertexAttributes(); // TO BE OPTIMIZED

	void buildMeshFromBatchedSprites();
	void copySpriteToMesh(const Sprite* sprite);
	void flush();

	std::vector<const Sprite*> batchedSprites;

	const BaseCamera* camera;
	ShaderProgram* selectedShader;
	ShaderProgram defaultShader;
	Mesh mesh;
	bool hasBegun;

	Texture* lastTexture;

};

#endif
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <cinttypes>
#include "render/VertexAttribute.h"
#include "math/Vector3.h"

class TextureRegion;

class Sprite
{
  public:

	explicit Sprite(const TextureRegion& _textureRegion);
	explicit Sprite(const TextureRegion& _textureRegion, int bottomLeftX, int bottomLeftY, int bottomLeftZ, int upperRightX, int upperRightY, int upperRightZ);
	explicit Sprite(const TextureRegion& _textureRegion, int bottomLeftX, int bottomLeftY, int bottomLeftZ, int upperRightX, int upperRightY, int upperRightZ, int originX, int originY,
	                int originZ);
	explicit Sprite(const TextureRegion& _textureRegion, int bottomLeftX, int bottomLeftY, int bottomLeftZ, int upperRightX, int upperRightY, int upperRightZ, int originX, int originY,
	                int originZ, int targetWidth, int targetHeight);

	void setPosition(int positionX, int positionY, int positionZ);

  private:

	static const int32_t VERTEX_SIZE = 3 + 3 + 2; // position + color + texcoords
	static constexpr int32_t SPRITE_SIZE = VERTEX_SIZE << 2; // floats * 4 bytes/float

	const TextureRegion& textureRegion;
	float vertices[SPRITE_SIZE]; // 32

	Vec3f origin;


};

#endif // _SPRITE_H_
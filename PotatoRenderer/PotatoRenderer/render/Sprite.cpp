#include "Sprite.h"

Sprite::Sprite(const TextureRegion& _textureRegion) : Sprite(_textureRegion, 0.0f, 0.0f, 0.0f, (float)_textureRegion.getWidth(), (float)_textureRegion.getHeight(), 0.0f)
{

}

Sprite::Sprite(const TextureRegion& _textureRegion, float _bottomLeftX, float _bottomLeftY, float _bottomLeftZ, float _upperRightX, float _upperRightY, float _upperRightZ) :
	Sprite(_textureRegion, _bottomLeftX, _bottomLeftY, _bottomLeftZ, _upperRightX, _upperRightY, _upperRightZ, (_upperRightX - _bottomLeftX) / 2, (_upperRightY - _bottomLeftY) / 2,
	       (_upperRightZ - _bottomLeftX) / 2)
{

}

Sprite::Sprite(const TextureRegion& _textureRegion, float _bottomLeftX, float _bottomLeftY, float _bottomLeftZ, float _upperRightX, float _upperRightY, float _upperRightZ,
               float _originX, float _originY, float _originZ) :
	textureRegion(_textureRegion),
	origin(_originX, _originY, _originZ),
	color(Color::WHITE),
	dirty(false)
{
	updatePosition(_bottomLeftX, _bottomLeftY, _bottomLeftZ, _upperRightX, _upperRightY, _upperRightZ);
	updateColor();
	updateUVs();
}


const std::array<float, Sprite::SPRITE_SIZE>& Sprite::getVertices() const
{
	if (dirty)
	{
		// Update rotation, scale, etc...
	}

	return vertices;
}

void Sprite::updatePosition(float bottomLeftX, float bottomLeftY, float bottomLeftZ, float upperRightX, float upperRightY, float upperRightZ)
{
	vertices[X1] = bottomLeftX;
	vertices[Y1] = bottomLeftY; //1
	vertices[Z1] = bottomLeftZ;

	vertices[X2] = upperRightX;
	vertices[Y2] = bottomLeftY; //2
	vertices[Z2] = upperRightZ;

	vertices[X3] = bottomLeftX;
	vertices[Y3] = upperRightY; //3
	vertices[Z3] = bottomLeftZ;

	vertices[X4] = upperRightX;
	vertices[Y4] = upperRightY; //4
	vertices[Z4] = upperRightZ;

	vertices[X5] = bottomLeftX;
	vertices[Y5] = upperRightY; //3
	vertices[Z5] = bottomLeftZ;

	vertices[X6] = upperRightX;
	vertices[Y6] = bottomLeftY; //2
	vertices[Z6] = upperRightZ;
}

void Sprite::updateColor()
{
	float colorFloatBits = color.toFloatBits();
	vertices[C1] = colorFloatBits;
	vertices[C2] = colorFloatBits;
	vertices[C3] = colorFloatBits;
	vertices[C4] = colorFloatBits;
	vertices[C5] = colorFloatBits;
	vertices[C6] = colorFloatBits;
}

void Sprite::updateUVs()
{
	vertices[U1] = textureRegion.getU1();
	vertices[V1] = textureRegion.getV1();

	vertices[U2] = textureRegion.getU2();
	vertices[V2] = textureRegion.getV1();

	vertices[U3] = textureRegion.getU1();
	vertices[V3] = textureRegion.getV2();

	vertices[U4] = textureRegion.getU2();
	vertices[V4] = textureRegion.getV2();

	vertices[U5] = textureRegion.getU1();
	vertices[V5] = textureRegion.getV2();

	vertices[U6] = textureRegion.getU2();
	vertices[V6] = textureRegion.getV1();
}
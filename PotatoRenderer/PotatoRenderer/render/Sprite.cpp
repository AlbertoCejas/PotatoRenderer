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
	color(Color::RED),
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
	vertices[CR1] = color.r;
	vertices[CG1] = color.g;
	vertices[CB1] = color.b;
	vertices[CR2] = color.r;
	vertices[CG2] = color.g;
	vertices[CB2] = color.b;
	vertices[CR3] = color.r;
	vertices[CG3] = color.g;
	vertices[CB3] = color.b;
	vertices[CR4] = color.r;
	vertices[CG4] = color.g;
	vertices[CB4] = color.b;
	vertices[CR5] = color.r;
	vertices[CG5] = color.g;
	vertices[CB5] = color.b;
	vertices[CR6] = color.r;
	vertices[CG6] = color.g;
	vertices[CB6] = color.b;
}

void Sprite::updateUVs()
{
	/*vertices[U1] = textureRegion.getU1();
	vertices[V1] = textureRegion.getV1();

	vertices[U2] = textureRegion.getU2();
	vertices[V2] = textureRegion.getV1();

	vertices[U3] = textureRegion.getU1();
	vertices[V3] = textureRegion.getV2();

	vertices[U4] = textureRegion.getU2();
	vertices[V4] = textureRegion.getV2();*/
}
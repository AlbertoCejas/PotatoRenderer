#include "Sprite.h"
#include "render/TextureRegion.h"

Sprite::Sprite(const TextureRegion& _textureRegion) : Sprite(_textureRegion, 0, 0, 0, _textureRegion.getWidth(), _textureRegion.getHeight(), 0)
{

}

Sprite::Sprite(const TextureRegion& _textureRegion, int _bottomLeftX, int _bottomLeftY, int _bottomLeftZ, int _upperRightX, int _upperRightY, int _upperRightZ) :
	Sprite(_textureRegion, _bottomLeftX, _bottomLeftY, _bottomLeftZ, _upperRightX, _upperRightY, _upperRightZ, (_upperRightX - _bottomLeftX) / 2, (_upperRightY - _bottomLeftY) / 2,
	       (_upperRightZ - _bottomLeftX) / 2)
{

}

Sprite::Sprite(const TextureRegion& _textureRegion, int _bottomLeftX, int _bottomLeftY, int _bottomLeftZ, int _upperRightX, int _upperRightY, int _upperRightZ, int _originX,
               int _originY, int _originZ) :
	Sprite(_textureRegion, _bottomLeftX, _bottomLeftY, _bottomLeftZ, _upperRightX, _upperRightY, _upperRightZ, _originX, _originY, _originZ,
	       (_upperRightX - _bottomLeftX), (_upperRightY - _bottomLeftY))
{

}

Sprite::Sprite(const TextureRegion& _textureRegion, int _bottomLeftX, int _bottomLeftY, int _bottomLeftZ, int _upperRightX, int _upperRightY, int _upperRightZ, int _originX,
               int _originY, int _originZ, int _targetWidth, int _targetHeight)
{

}
#include "render/TextureRegion.h"
#include "render/Texture.h"
#include <cmath>

TextureRegion::TextureRegion(const Texture& _texture) : TextureRegion(_texture, 0, 0, _texture.getWidth(), _texture.getHeight())
{

}

TextureRegion::TextureRegion(const Texture& _texture, int _x, int _y, int _width, int _height) : texture(_texture)
{
	setRegion(_x, _y, _width, _height);
}

void TextureRegion::setRegion(int _x, int _y, int _width, int _height)
{
	float invTexWidth = 1.0f / texture.getWidth();
	float invTexHeight = 1.0f / texture.getHeight();
	setRegion(_x * invTexWidth, _y * invTexHeight, (_x + width) * invTexWidth, (_y + height) * invTexHeight);
	width = _width;
	height = _height;
}

void TextureRegion::setRegion(float _u, float _v, float _u2, float _v2)
{
	int texWidth = texture.getWidth(), texHeight = texture.getHeight();

	width = (int) std::round(std::abs(_u2 - _u) * texWidth);
	height = (int) std::round(std::abs(_v2 - _v) * texHeight);

	u = _u;
	v = _v;
	u2 = _u2;
	v2 = _v2;
}
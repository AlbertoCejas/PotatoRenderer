#ifndef _TEXTURE_REGION_H_
#define _TEXTURE_REGION_H_

#include <cinttypes>

class Texture;

class TextureRegion
{
  public:

	explicit TextureRegion(const Texture& _texture);
	explicit TextureRegion(const Texture& _texture, int _x, int _y, int _width, int _height);

	inline const Texture& getTexture() const { return texture; }
	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

	void setRegion(int x, int y, int width, int height);

  private:

	void setRegion(float u, float v, float u2, float v2);

	const Texture& texture;
	float u, v;
	float u2, v2;
	int32_t width;
	int32_t height;

};

#endif // _TEXTURE_REGION_H_
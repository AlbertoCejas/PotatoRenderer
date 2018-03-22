#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <cinttypes>

enum class TextureFilter;
enum class TextureWrap;

class Texture
{
  public:

	explicit Texture(const char* _path);
	Texture(const char* _path, TextureFilter _minFilter, TextureFilter _magFilter, TextureWrap _uWrap, TextureWrap _vWrap, bool _generateMipMaps);
	~Texture();

	inline int getTextureUnitIndex() const { return textureUnitIndex; }
	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }
	inline int getNumOfChannels() const { return numOfChannels; }
	inline TextureFilter getMinFilter() const { return minFilter; }
	inline TextureFilter getMagFilter() const { return magFilter; }
	inline TextureWrap getUWrap() const { return uWrap; }
	inline TextureWrap getVWrap() const { return vWrap; }
	// inline const unsigned char* getData() const { return data; }

	void bindTexture();
	void unbindTexture();

  private:

	static const int32_t MAX_BOUNDED_TEXTURES;
	static int32_t CURRENTLY_BOUNDED_TEXTURE_UNITS_MASK;

	unsigned char* loadData(const char* path);
	void uploadTexture(unsigned char* data);


	uint32_t handler;
	int32_t textureUnitIndex;

	//unsigned char* data;
	TextureFilter minFilter;
	TextureFilter magFilter;
	TextureWrap uWrap;
	TextureWrap vWrap;
	int32_t width;
	int32_t height;
	int32_t numOfChannels;
	bool generateMipMaps;
};

#endif
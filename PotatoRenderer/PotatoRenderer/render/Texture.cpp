#define STB_IMAGE_IMPLEMENTATION
#include "utils/stb_image.h"
#include "render/Texture.h"
#include "render/GLEnums.h"
#include <cstring>
#include <algorithm>
#include "utils/BitwiseUtils.h"

const int32_t Texture::MAX_BOUNDED_TEXTURES = sizeof(Texture::CURRENTLY_BOUNDED_TEXTURE_UNITS_MASK) << 3;
int32_t Texture::CURRENTLY_BOUNDED_TEXTURE_UNITS_MASK = 0;

Texture::Texture(const char* _path) : Texture(_path, TextureFilter::LINEAR, TextureFilter::LINEAR, TextureWrap::REPEAT, TextureWrap::REPEAT, true)
{
}

Texture::Texture(const char* _path, TextureFilter _minFilter, TextureFilter _magFilter, TextureWrap _uWrap, TextureWrap _vWrap, bool _generateMipMaps) :
	textureUnitIndex(-1),
	minFilter(_minFilter),
	magFilter(_magFilter),
	uWrap(_uWrap),
	vWrap(_vWrap),
	generateMipMaps(_generateMipMaps)
{
	unsigned char* data = loadData(_path);
	uploadTexture(data);
	stbi_image_free(data);
}

Texture::~Texture()
{
}

unsigned char* Texture::loadData(const char* path)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &numOfChannels, 0);
	assert(data != nullptr);
	return data;
}

void Texture::uploadTexture(unsigned char* data)
{
	glGenTextures(1, &handler);

	bindTexture();

	// Set our texture wrapping
	glTexParameteri(GL_TEXTURE_2D, (int) TextureParameter::WRAP_S, (int) uWrap);   // Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, (int) TextureParameter::WRAP_T, (int) vWrap);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, (int)TextureParameter::MIN_FILTER, (int) minFilter);
	glTexParameteri(GL_TEXTURE_2D, (int)TextureParameter::MAG_FILTER, (int) magFilter);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	if (generateMipMaps)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void Texture::bindTexture()
{
	if (textureUnitIndex == -1)
	{
		assert(BitwiseUtils::allOne(Texture::CURRENTLY_BOUNDED_TEXTURE_UNITS_MASK) == false);
		textureUnitIndex = BitwiseUtils::getFirstZeroIndex(Texture::CURRENTLY_BOUNDED_TEXTURE_UNITS_MASK);
		BitwiseUtils::setNBit(CURRENTLY_BOUNDED_TEXTURE_UNITS_MASK, textureUnitIndex);
	}

	glActiveTexture((int) TextureUnit::TEXTURE_UNIT_0 + textureUnitIndex);
	glBindTexture(GL_TEXTURE_2D, handler); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
}

void Texture::unbindTexture()
{
	if (textureUnitIndex != -1)
	{
		BitwiseUtils::resetNBit(CURRENTLY_BOUNDED_TEXTURE_UNITS_MASK, textureUnitIndex);
		textureUnitIndex = -1;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}
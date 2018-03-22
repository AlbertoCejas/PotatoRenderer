#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <cinttypes>
#include "render/VertexAttribute.h"
#include "render/TextureRegion.h"
#include "math/Vector3.h"
#include "render/Color.h"
#include <array>

class TextureRegion;

class Sprite
{
  private:

	static const int32_t VERTEX_SIZE = 3 + 3 + 2; // position + color + texcoords = 8

	/*

	x3 ----- x4
	   |   |
	   |   |
	x1 ----- x2

	*/

	static const int32_t X1 = 0;
	static const int32_t Y1 = 1;
	static const int32_t Z1 = 2;
	static const int32_t CR1 = 3;
	static const int32_t CG1 = 4;
	static const int32_t CB1 = 5;
	static const int32_t U1 = 6;
	static const int32_t V1 = 7;
	static const int32_t X2 = 8;
	static const int32_t Y2 = 9;
	static const int32_t Z2 = 10;
	static const int32_t CR2 = 11;
	static const int32_t CG2 = 12;
	static const int32_t CB2 = 13;
	static const int32_t U2 = 14;
	static const int32_t V2 = 15;
	static const int32_t X3 = 16;
	static const int32_t Y3 = 17;
	static const int32_t Z3 = 18;
	static const int32_t CR3 = 19;
	static const int32_t CG3 = 20;
	static const int32_t CB3 = 21;
	static const int32_t U3 = 22;
	static const int32_t V3 = 23;
	static const int32_t X4 = 24;
	static const int32_t Y4 = 25;
	static const int32_t Z4 = 26;
	static const int32_t CR4 = 27;
	static const int32_t CG4 = 28;
	static const int32_t CB4 = 29;
	static const int32_t U4 = 30;
	static const int32_t V4 = 31;

  public:

	static constexpr int32_t SPRITE_SIZE = VERTEX_SIZE << 2; // floats * 4 bytes/float  = 8 * 4 = 32

	explicit Sprite(const TextureRegion& _textureRegion);
	explicit Sprite(const TextureRegion& _textureRegion, float bottomLeftX, float bottomLeftY, float bottomLeftZ, float upperRightX, float upperRightY, float upperRightZ);
	explicit Sprite(const TextureRegion& _textureRegion, float bottomLeftX, float bottomLeftY, float bottomLeftZ, float upperRightX, float upperRightY, float upperRightZ,
	                float originX, float originY, float originZ); // Origin is relative to bottom-left corner

	inline const TextureRegion& getTextureRegion() const { return textureRegion; }
	const std::array<float, SPRITE_SIZE>& getVertices() const;
	inline const Color& getColor() const { return color; }

	inline void setColor(const Color& _color) { color = _color; updateColor(); }


  private:

	void updatePosition(float bottomLeftX, float bottomLeftY, float bottomLeftZ, float upperRightX, float upperRightY, float upperRightZ);
	void updateColor();
	void updateUVs();

	TextureRegion textureRegion;
	std::array<float, SPRITE_SIZE> vertices;

	Vec3f origin;
	Color color;

	bool dirty;
};

#endif // _SPRITE_H_
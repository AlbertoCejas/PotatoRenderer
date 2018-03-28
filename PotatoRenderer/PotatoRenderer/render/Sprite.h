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

	static const int32_t VERTEX_SIZE = 3 + 1 + 2; // position + color + texcoords = 9

	/*

	x3x5 ---- x4
	     |   |
	     |   |
	  x1 ---- x2x6

	*/

	static const int32_t X1 = 0;
	static const int32_t Y1 = 1;
	static const int32_t Z1 = 2;
	static const int32_t C1 = 3;
	static const int32_t U1 = 4;
	static const int32_t V1 = 5;
	static const int32_t X2 = 6;
	static const int32_t Y2 = 7;
	static const int32_t Z2 = 8;
	static const int32_t C2 = 9;
	static const int32_t U2 = 10;
	static const int32_t V2 = 11;
	static const int32_t X3 = 12;
	static const int32_t Y3 = 13;
	static const int32_t Z3 = 14;
	static const int32_t C3 = 15;
	static const int32_t U3 = 16;
	static const int32_t V3 = 17;
	static const int32_t X4 = 18;
	static const int32_t Y4 = 19;
	static const int32_t Z4 = 20;
	static const int32_t C4 = 21;
	static const int32_t U4 = 22;
	static const int32_t V4 = 23;
	static const int32_t X5 = 24;
	static const int32_t Y5 = 25;
	static const int32_t Z5 = 26;
	static const int32_t C5 = 27;
	static const int32_t U5 = 28;
	static const int32_t V5 = 29;
	static const int32_t X6 = 30;
	static const int32_t Y6 = 31;
	static const int32_t Z6 = 32;
	static const int32_t C6 = 33;
	static const int32_t U6 = 34;
	static const int32_t V6 = 35;

  public:

	static constexpr int32_t SPRITE_SIZE = VERTEX_SIZE * 6; // floats * 4 bytes/float  = 8 * 4 = 32

	explicit Sprite(const TextureRegion& _textureRegion);
	explicit Sprite(const TextureRegion& _textureRegion, float bottomLeftX, float bottomLeftY, float bottomLeftZ, float upperRightX, float upperRightY, float upperRightZ);
	explicit Sprite(const TextureRegion& _textureRegion, float bottomLeftX, float bottomLeftY, float bottomLeftZ, float upperRightX, float upperRightY, float upperRightZ,
	                float originX, float originY, float originZ); // Origin is relative to bottom-left corner

	inline TextureRegion& getTextureRegion() { return textureRegion; }
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
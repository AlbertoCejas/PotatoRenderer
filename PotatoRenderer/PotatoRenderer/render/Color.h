#ifndef _COLOR_H_
#define _COLOR_H_

#include <stdint.h>
#include <cstdint>

class Color
{
  public:

	static const Color BLUE;
	static const Color RED;
	static const Color GREEN;
	static const Color YELLOW;
	static const Color PINK;
	static const Color ORANGE;
	static const Color BLACK;
	static const Color LIGHT_GRAY;
	static const Color GRAY;
	static const Color DARK_GRAY;
	static const Color WHITE;

	static float toFloatBits(float _r, float _g, float _b, float _a);


	Color(float red, float green, float blue, float alpha) : r(red), g(green), b(blue), a(alpha)
	{
		clampComponents();
	}

	Color& set(const Color& color);
	Color& set(float _r, float _g, float _b, float _a);

	uint32_t toIntBits() const;
	float toFloatBits() const;

	float r;
	float g;
	float b;
	float a;

  private:

	union int_float_bits
	{
		uint32_t int_bits;
		float float_bits;
	};

	void clampComponents();
};


#endif // _COLOR_H_
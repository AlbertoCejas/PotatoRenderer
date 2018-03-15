#include "Color.h"
#include "math/MathUtils.h"

const Color Color::BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const Color Color::RED(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
const Color Color::PINK(1.0f, 0.752941f, 0.796078f, 1.0f);
const Color Color::ORANGE(1.0f, 0.647059f, 0.0f, 1.0f);
const Color Color::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::WHITE(1.0f, 1.0f, 1.0f, 1.0f);

Color& Color::set(const Color& color)
{
	return set(color.r, color.g, color.b, color.a);
}

Color& Color::set(float _r, float _g, float _b, float _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
	clampComponents();
	return *this;
}

void Color::clampComponents()
{
	MathUtils::clamp<float>(r, 0.0f, 1.0f);
	MathUtils::clamp<float>(g, 0.0f, 1.0f);
	MathUtils::clamp<float>(b, 0.0f, 1.0f);
	MathUtils::clamp<float>(a, 0.0f, 1.0f);
}

uint32_t Color::toIntBits() const
{
	uint32_t color = ((uint32_t)(255 * a) << 24) | ((uint32_t)(255 * b) << 16) | ((uint32_t)(255 * g) << 8) | ((uint32_t)(255 * r));
	return color;
}

float Color::toFloatBits() const
{
	union int_float_bits color;
	color.int_bits = this->toIntBits() & 0xfeffffff;
	return color.float_bits;
}
float Color::toFloatBits(float _r, float _g, float _b, float _a)
{
	int color = ((int)(255 * _a) << 24) | ((int)(255 * _b) << 16) | ((int)(255 * _g) << 8) | ((int)(255 * _r));
	union int_float_bits colorIntFloat;
	colorIntFloat.int_bits = color & 0xfeffffff;
	return colorIntFloat.float_bits;
}
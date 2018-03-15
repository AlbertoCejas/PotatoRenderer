#ifndef _MATH_UTILS_H_
#define _MATH_UTILS_H_

#pragma warning( disable: 4505 )

#define _USE_MATH_DEFINES
#include "math.h"

#include <climits>

namespace MathUtils
{
	static const float PI = (float) M_PI;
	static const float PI2 = PI * 2.0f;

	// static float radiansToDegrees(float radians) { return radians * 180.0f / PI; }
	static float degreesToRadians(float degrees) { return degrees * PI / 180.0f; }

	template<typename T>
	static bool areEqual(const T x, const T y)
	{
		// the machine epsilon has to be scaled to the magnitude of the values used
		// and multiplied by the desired precision in ULPs (units in the last place)
		return std::abs(x - y) <= std::numeric_limits<T>::epsilon() * std::abs(x + y) * 2
		       // unless the result is subnormal
		       || std::abs(x - y) < std::numeric_limits<T>::min();
	}

}

#endif
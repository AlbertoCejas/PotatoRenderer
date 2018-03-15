#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "math/MathUtils.h"
#include "math/Vector3.h"

class Quaternion
{
  public:

	explicit Quaternion() : Quaternion(.0f, .0f, .0f, 1.0f) { }
	explicit Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) { }

	Quaternion(const Quaternion& other) : Quaternion(other.x, other.y, other.z, other.w) { }

	Quaternion& identity()
	{
		return this->set(.0f, .0f, .0f, 1.0f);
	}

	inline Quaternion& set(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		return *this;
	}

	Quaternion& setToAxisRotationDegrees(float _x, float _y, float _z, float _degrees)
	{
		return setToAxisRotationRadians(_x, _y, _z, MathUtils::degreesToRadians(_degrees));
	}

	Quaternion& setToAxisRotationRadians(float _x, float _y, float _z, float _radians)
	{
		Vec3f vector(_x, _y, _z);
		float d = vector.length();

		if (d == .0f)
		{
			return identity();
		}

		d = 1.0f / d;

		using namespace MathUtils;

		float l_ang = _radians < .0f ? PI2 - std::fmodf(-_radians, PI2) : std::fmodf(_radians, PI2);
		float l_sin = (float)std::sin(l_ang / 2);
		float l_cos = (float)std::cos(l_ang / 2);
		return this->set(d * _x * l_sin, d * _y * l_sin, d * _z * l_sin, l_cos).normalize();
	}

	float lengthSqrt() const
	{
		return x * x + y * y + z * z + w * w;
	}

	Quaternion& normalize()
	{
		float len = lengthSqrt();

		if (len != 0.f && !MathUtils::areEqual(len, 1.0f))
		{
			len = (float)std::sqrt(len);
			w /= len;
			x /= len;
			y /= len;
			z /= len;
		}

		return *this;
	}


  public:

	float x;
	float y;
	float z;
	float w;

};

#endif //_QUATERNION_H_
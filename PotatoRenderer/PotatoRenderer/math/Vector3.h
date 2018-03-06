#ifndef _VECTOR_3_
#define _VECTOR_3_

#include <type_traits>
#include <cassert>
#include <cmath>
#include <cstdint>

template<typename T>
class Vector3
{
  public:

	static_assert(std::is_arithmetic<T>::value, "Type template must be a number");

	explicit Vector3() : x(0), y(0), z(0) { }
	explicit Vector3(T x, T y, T z) : x(x), y(y), z(z) { }

	Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) { }

	Vector3 operator+(const Vector3& other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3 operator-(const Vector3& other) const
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	Vector3 operator*(const Vector3& other) const
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	Vector3 operator/(const Vector3& other) const
	{
		assert(other.x != 0 && other.y != 0 && other.z != 0);
		return Vector3(x / other.x, y / other.y, z / other.z);
	}

	Vector3 operator+(T scalar) const
	{
		return Vector3(x + scalar, y + scalar, z + scalar);
	}

	Vector3 operator*(T scalar) const
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	Vector3& operator+=(const Vector3& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}

	Vector3& operator*=(const Vector3& other)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		return *this;
	}

	Vector3& operator/=(const Vector3& other)
	{
		assert(other.x != 0 && other.y != 0 && other.z != 0);

		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;
		return *this;
	}

	Vector3& operator+=(T scalar)
	{
		this->x += scalar;
		this->y += scalar;
		this->z += scalar;
		return *this;
	}

	Vector3& operator*=(T scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return *this;
	}

	Vector3& cross(const Vector3& other) const
	{
		return Vector3
		(
			y * other.z - z * other.y,
		    z * other.x - x * other.z,
		    x * other.y - y * other.x
		);
	}

	T dot(const Vector3& other) const
	{
		return (x * other.x) + (y * other.y) + (z * other.z);
	}

	T length() const
	{
		return std::sqrt((std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2)));
	}

	T lengthSqrt() const
	{
		return std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
	}

	const Vector3& normalize()
	{
		T length = length();
		assert(length != 0);
		*this = *this / length;
		return *this;
	}

  public:

	T x;
	T y;
	T z;

};

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
Vector3<T> operator+(T scalar, const Vector3<T>& vector)
{
	return vector + scalar;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
Vector3<T> operator*(T scalar, const Vector3<T>& vector)
{
	return vector + scalar;
}


using Vec3i = Vector3<int32_t>;
using Vec3f = Vector3<float>;
using Vec3d = Vector3<double>;

#endif
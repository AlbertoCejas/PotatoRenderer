#ifndef _MATRIX_TRANSFORMATIONS_H_
#define _MATRIX_TRANSFORMATIONS_H_

#define _USE_MATH_DEFINES

#include "math/Matrix.h"
#include "math/Vector3.h"
#include "math/Quaternion.h"
#include "math.h"

namespace MatrixTransformations
{
	template<typename T>
	static void lookAt(Matrix<T, 4, 4>& matrix, const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up) // Right-handed
	{
		Vector3<T> f((center - eye));
		f.normalize();
		Vector3<T> s(f);
		s.cross(up).normalize();
		Vector3<T> u(s);
		u.cross(f).normalize();

		matrix.identity();

		// Ordered by cache access (column-major)
		matrix(0, 0) = s.x;
		matrix(1, 0) = u.x;
		matrix(2, 0) = -f.x;

		matrix(0, 1) = s.y;
		matrix(1, 1) = u.y;
		matrix(2, 1) = -f.y;

		matrix(0, 2) = s.z;
		matrix(1, 2) = u.z;
		matrix(2, 2) = -f.z;

		matrix(0, 3) = -s.dot(eye);
		matrix(1, 3) = -u.dot(eye);
		matrix(2, 3) = f.dot(eye);
	}

	template<typename T>
	static void toOrtho(Matrix<T, 4, 4>& matrix, float left, float right, float bottom, float top, float near, float far) // Right-handed, depth clip space(-1,1)
	{
		matrix.identity();
		// Ordered by cache access (column-major)
		matrix(0, 0) = static_cast<T>(2) / (right - left);
		matrix(1, 1) = static_cast<T>(2) / (top - bottom);
		matrix(2, 2) = - static_cast<T>(2) / (far - near);
		matrix(0, 3) = -(right + left) / (right - left);
		matrix(1, 3) = -(top + bottom) / (top - bottom);
		matrix(2, 3) = -(far + near) / (far - near);
	}

	template<typename T>
	static void toPerspective(Matrix<T, 4, 4>& matrix, float near, float far, float fieldOfViewDegrees, float aspect) // Right-handed, depth clip space(-1,1)
	{
		assert(std::abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

		matrix.identity();

		const T fieldOfViewRadians = fieldOfViewDegrees * static_cast<T>(M_PI / 180.0);
		const T insideTan = fieldOfViewRadians / static_cast<T>(2);
		const T tanHalfFovy = std::tan(insideTan);

		// Ordered by cache access (column-major)
		matrix(0, 0) = static_cast<T>(1) / (aspect * tanHalfFovy);
		matrix(1, 1) = static_cast<T>(1) / (tanHalfFovy);
		matrix(2, 2) = - (far + near) / (far - near);
		matrix(3, 2) = - static_cast<T>(1);
		matrix(2, 3) = -(static_cast<T>(2) * far * near) / (far - near);
		matrix(3, 3) = static_cast<T>(0);
	}

	template <typename T>
	static void rotate(Matrix<T, 4, 4>& target, float axisX, float axisY, float axisZ, float degrees)
	{
		if (degrees == .0f)
		{
			target.identity();
			return;
		}

		Quaternion quaternion;
		quaternion.setToAxisRotationDegrees(axisX, axisY, axisZ, degrees);
		rotate(target, quaternion);
	};

	template <typename T>
	static void rotate(Matrix<T, 4, 4>& target, const Quaternion& quaternion)
	{
		Matrix<T, 4, 4> matrix = transformToMatrix<T>(quaternion);
		target *= matrix;
	};

	template <typename T>
	static Matrix<T, 4, 4> transformToMatrix(const Quaternion& quaternion)
	{
		const T xx = quaternion.x * quaternion.x;
		const T xy = quaternion.x * quaternion.y;
		const T xz = quaternion.x * quaternion.z;
		const T xw = quaternion.x * quaternion.w;
		const T yy = quaternion.y * quaternion.y;
		const T yz = quaternion.y * quaternion.z;
		const T yw = quaternion.y * quaternion.w;
		const T zz = quaternion.z * quaternion.z;
		const T zw = quaternion.z * quaternion.w;

		Matrix<T, 4, 4> matrix;

		// Ordered by cache access (column-major)
		matrix(0, 0) = (T)1 - (T)2 * (yy + zz);
		matrix(0, 1) = (T)2 * (xy - zw);
		matrix(0, 2) = (T)2 * (xz + yw);
		matrix(0, 3) = (T)0;
		matrix(1, 0) = (T)2 * (xy + zw);
		matrix(1, 1) = (T)1 - (T)2 * (xx + zz);
		matrix(1, 2) = (T)2 * (yz - xw);
		matrix(1, 3) = (T)0;
		matrix(2, 0) = (T)2 * (xz - yw);
		matrix(2, 1) = (T)2 * (yz + xw);
		matrix(2, 2) = (T)1 - (T)2 * (xx + yy);
		matrix(2, 3) = (T)0;
		matrix(3, 0) = (T)0;
		matrix(3, 1) = (T)0;
		matrix(3, 2) = (T)0;
		matrix(3, 3) = (T)1;

		return matrix;
	}

	template <typename T>
	static void applyTransform(Matrix<T, 4, 4>& target, T translationX, T translationY, T translationZ, T quaternionX, T quaternionY, T quaternionZ, T quaternionW,
	                           T scaleX, T scaleY, T scaleZ)
	{
		const T xs = quaternionX * (T)2;
		const T ys = quaternionY * (T)2;
		const T zs = quaternionZ * (T)2;
		const T wx = quaternionW * xs;
		const T wy = quaternionW * ys;
		const T wz = quaternionW * zs;
		const T xx = quaternionX * xs;
		const T xy = quaternionX * ys;
		const T xz = quaternionX * zs;
		const T yy = quaternionY * ys;
		const T yz = quaternionY * zs;
		const T zz = quaternionZ * zs;

		// Ordered by cache access (column-major)

		matrix(0, 0) = scaleX * ((T)1 - (yy + zz));
		matrix(1, 0) = scaleX * (xy + wz);
		matrix(2, 0) = scaleX * (xz + wy);
		matrix(3, 0) = (T)0;

		matrix(0, 1) = scaleY * (xy - wz);
		matrix(1, 1) = scaleY * ((T)1 - (xx + zz));
		matrix(2, 1) = scaleY * (yz + wx);
		matrix(3, 1) = (T)0;

		matrix(0, 2) = scaleZ * (xz + wy);
		matrix(1, 2) = scaleZ * (yz - wx);
		matrix(2, 2) = scaleZ * ((T)1 - (xx + yy));
		matrix(3, 2) = (T)0;

		matrix(0, 3) = translationX;
		matrix(1, 3) = translationY;
		matrix(2, 3) = translationZ;
		matrix(3, 3) = (T)1;
	}
};

#endif
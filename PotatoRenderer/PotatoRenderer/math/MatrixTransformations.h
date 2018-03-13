#ifndef _MATRIX_TRANSFORMATIONS_H_
#define _MATRIX_TRANSFORMATIONS_H_

#define _USE_MATH_DEFINES

#include "math/Matrix.h"
#include "math/Vector3.h"
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
		/*

		float l_fd = (float)(1.0 / std::tan((fieldOfViewDegrees * (M_PI / 180)) / 2.0));
		float l_a1 = (far + near) / (near - far);
		float l_a2 = (2 * far * near) / (near - far);

		matrix[0][0] = l_fd / aspect;
		matrix[1][1] = l_fd;
		matrix[2][2] = l_a1;
		matrix[2][3] = l_a2;
		matrix[3][2] = -1;
		matrix[3][3] = static_cast<T>(0);

		*/

		const T fieldOfViewRadians = fieldOfViewDegrees * static_cast<T>(M_PI / 180.0);
		const T insideTan = fieldOfViewRadians / static_cast<T>(2);
		const T tanHalfFovy = std::tan(insideTan);

		matrix(0, 0) = static_cast<T>(1) / (aspect * tanHalfFovy);
		matrix(1, 1) = static_cast<T>(1) / (tanHalfFovy);
		matrix(2, 2) = - (far + near) / (far - near);
		matrix(3, 2) = - static_cast<T>(1);
		matrix(2, 3) = -(static_cast<T>(2) * far * near) / (far - near);
		matrix(3, 3) = static_cast<T>(0);
	}

	template <typename T, int ROW_DIM, int COL_DIM>
	static void rotate(Matrix<T, ROW_DIM, COL_DIM>& target, const Vector3<float>& axis, float degrees)
	{
		if (degrees == .0f)
		{
			target.identity();
			return;
		}

		Quaternion<T> quaternion(axis, degrees);
		rotate(target, quaternion);
	};

	template <typename T, int ROW_DIM, int COL_DIM>
	static void rotate(Matrix<T, ROW_DIM, COL_DIM>& target, const Quaternion<T>& quaternion)
	{

	};

#endif
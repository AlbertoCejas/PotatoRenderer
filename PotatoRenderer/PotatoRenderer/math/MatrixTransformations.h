#ifndef _MATRIX_TRANSFORMATIONS_H_
#define _MATRIX_TRANSFORMATIONS_H_

#include "math/Matrix.h"
#include "math/Vector3.h"

namespace MatrixTransformations
{
	template<typename T>
	static void lookAt(Matrix<T, 4, 4>& matrix, const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up)
	{
		Vector3<T> f((center - eye));
		f.normalize();
		Vector3<T> s(f);
		s.cross(up).normalize();
		Vector3<T> u(s);
		u.cross(f).normalize();

		matrix.identity();

		matrix[0][0] = s.x;
		matrix[1][0] = s.y;
		matrix[2][0] = s.z;
		matrix[0][1] = u.x;
		matrix[1][1] = u.y;
		matrix[2][1] = u.z;
		matrix[0][2] = f.x;
		matrix[1][2] = f.y;
		matrix[2][2] = f.z;
		matrix[3][0] = s.dot(eye);
		matrix[3][1] = -u.dot(eye);
		matrix[3][2] = -f.dot(eye);
	}

	template<typename T>
	static void toOrtho(Matrix<T, 4, 4>& matrix, float left, float right, float bottom, float top, float near, float far)
	{
		matrix.identity();
		matrix[0][0] = 2 / (right - left);
		matrix[1][1] = 2 / (top - bottom);
		matrix[2][2] = -2 / (far - near);
		matrix[3][0] = -(right + left) / (right - left);
		matrix[3][1] = -(top + bottom) / (top - bottom);
		matrix[3][2] = -(far + near) / (far - near);
	}

};

#endif
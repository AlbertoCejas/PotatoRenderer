#ifndef _VECTOR_TRANSFORMATION_H_
#define _VECTOR_TRANSFORMATION_H_

#include "math/Matrix.h"
#include "math/Vector3.h"
#include "math/MatrixTransformations.h"

namespace VectorTransformations
{
	template<typename T>
	static void rotate(Vector3<T>& target, const Vector3<float>& axis, float degrees)
	{
		Mat4f matrix;
		MatrixTransformations::rotate(matrix, axis, angle);
		target *= matrix;
	}
};

#endif
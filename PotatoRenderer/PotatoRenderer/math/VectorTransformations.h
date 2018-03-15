#ifndef _VECTOR_TRANSFORMATION_H_
#define _VECTOR_TRANSFORMATION_H_

#include "math/Matrix.h"
#include "math/Vector3.h"
#include "math/MatrixTransformations.h"

namespace VectorTransformations
{
	template<typename T>
	static void rotateDegrees(Vector3<T>& target, float axisX, float axisY, float axisZ, float degrees)
	{
		Mat4f matrix;
		MatrixTransformations::rotate<T>(matrix, axisX, axisY, axisZ, degrees);
		applyTransformation(target, matrix);
	}

	template<typename T>
	static void applyTransformation(Vector3<T>& target, const Matrix<T, 4, 4>& transformationMatrix)
	{
		target.set
		(
		    target.x * transformationMatrix(0, 0) + target.y * transformationMatrix(0, 1) + target.z * transformationMatrix(0, 2) + transformationMatrix(0, 3),
		    target.x * transformationMatrix(1, 0) + target.y * transformationMatrix(1, 1) + target.z * transformationMatrix(1, 2) + transformationMatrix(1, 3),
		    target.x * transformationMatrix(2, 0) + target.y * transformationMatrix(2, 1) + target.z * transformationMatrix(2, 2) + transformationMatrix(2, 3)
		);
	}
};

#endif
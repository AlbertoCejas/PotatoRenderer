#include "BaseCamera.h"
#include <cmath>
#include "math/VectorTransformations.h"

BaseCamera::BaseCamera(float _viewportWidth, float _viewportHeight) :
	viewportWidth(_viewportWidth),
	viewportHeight(_viewportHeight),
	up(0.0f, 1.0f, 0.0f),
	near(1.0f),
	far(100.0f),
	direction(0.0f, 0.0f, -1.0f)
{ }

/*
void BaseCamera::lookAt(const Vec3f& vec)
{
    lookAt(vec.x, vec.y, vec.z);
}

void BaseCamera::lookAt(float x, float y, float z)
{
    cachedVector.set(x, y, z).sub(position).normalize();

    if (!cachedVector.isZero())
    {
        float dot = cachedVector.dot(up); // up and direction must ALWAYS be orthonormal vectors

        if (std::abs(dot - 1) < 0.000000001f)
        {
            // Collinear
            up.set(direction).mul(-1);
        }
        else if (std::abs(dot + 1) < 0.000000001f)
        {
            // Collinear opposite
            up.set(direction);
        }

        direction.set(cachedVector);
        normalizeUp();
    }
}
*/

void BaseCamera::rotateDegrees(float axisX, float axisY, float axisZ, float angle)
{
	VectorTransformations::rotateDegrees<float>(direction, axisX, axisY, axisZ, angle);
	VectorTransformations::rotateDegrees<float>(up, axisX, axisY, axisZ, angle);
}

void BaseCamera::normalizeUp()
{
	cachedVector.set(direction).cross(up).normalize();
	up.set(cachedVector).cross(direction).normalize();
}
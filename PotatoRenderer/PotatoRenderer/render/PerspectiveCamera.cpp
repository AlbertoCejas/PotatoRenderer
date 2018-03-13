#include "render/PerspectiveCamera.h"
#include "math/MatrixTransformations.h"
#include <cmath>

const float PerspectiveCamera::DEFAULT_FIELD_OF_VIEW_DEGREES = 67.0f;

PerspectiveCamera::PerspectiveCamera(float _fieldOfViewDegrees, float _viewportWidth, float _viewportHeight) : BaseCamera(_viewportWidth, _viewportHeight),
	fieldOfViewDegrees(_fieldOfViewDegrees)
{
	update();
}

void PerspectiveCamera::update()
{
	MatrixTransformations::toPerspective<float>(projection, near, far, fieldOfViewDegrees, viewportWidth / viewportHeight);
	MatrixTransformations::lookAt<float>(this->view, position, position + direction, up);

	projectionViewCombined.setData(this->projection.getData());
	projectionViewCombined *= this->view;
}
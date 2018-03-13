#include "OrthographicCamera.h"
#include "math/MatrixTransformations.h"

/*
void OrthographicCamera::setToOrtho(float _viewportWidth, float _viewportHeight)
{
    up.set(0, 1, 0);
    direction.set(0, 0, -1);

    position.set(zoom * _viewportWidth / 2.0f, zoom * _viewportHeight / 2.0f, 0);
    viewportWidth = _viewportWidth;
    viewportHeight = _viewportHeight;
    update();
}
*/

void OrthographicCamera::update()
{
	MatrixTransformations::toOrtho<float>(this->projection, zoom * -viewportWidth / 2, zoom * (viewportWidth / 2), zoom * -(viewportHeight / 2), zoom * viewportHeight / 2, near, far);
	MatrixTransformations::lookAt<float>(this->view, position, position + direction, up);

	projectionViewCombined.setData(this->projection.getData());
	projectionViewCombined *= this->view;
}
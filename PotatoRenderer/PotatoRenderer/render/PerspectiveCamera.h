#ifndef _PERSPECTIVE_CAMERA_H_
#define _PERSPECTIVE_CAMERA_H_

#include "render/BaseCamera.h"

class PerspectiveCamera : public BaseCamera
{
  public:

	PerspectiveCamera(float _viewportWidth, float _viewportHeight) : PerspectiveCamera(DEFAULT_FIELD_OF_VIEW_DEGREES, _viewportWidth, _viewportHeight) { }
	PerspectiveCamera(float _fieldOfViewDegrees, float _viewportWidth, float _viewportHeight);
	~PerspectiveCamera() { }

	void update() override;

  private:

	static const float DEFAULT_FIELD_OF_VIEW_DEGREES;

	float fieldOfViewDegrees;

};

#endif // _PERSPECTIVE_CAMERA_H_
#ifndef _ORTHOGRAPHIC_CAMERA_H_
#define _ORTHOGRAPHIC_CAMERA_H_

#include "render/BaseCamera.h"

class OrthographicCamera : public BaseCamera
{
  public:

	OrthographicCamera(float _viewportWidth, float _viewportHeight) : BaseCamera(_viewportWidth, _viewportHeight), zoom(1.0f)
	{
		near = .0f;
		update();
	}

	~OrthographicCamera() { }

	void setToOrtho(float viewportWidth, float viewportHeight);

	void update() override;

  private:

	float zoom;

};

#endif _ORTHOGRAPHIC_CAMERA_H_


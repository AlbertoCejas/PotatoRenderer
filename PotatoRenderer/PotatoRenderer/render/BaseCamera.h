#ifndef _BASE_CAMERA_H_
#define _BASE_CAMERA_H_

#include "math/Matrix.h"
#include "math/Vector3.h"

class BaseCamera
{
  public:

	explicit BaseCamera(float _viewportWidth, float _viewportHeight);
	virtual ~BaseCamera() { }

	inline const Mat4f& GetCombined() const { return projectionViewCombined; }

	virtual void translate(const Vec3f& vec) { position += vec; }
	virtual void translate(float x, float y, float z) { position.add(x, y, z); }

	void lookAt(const Vec3f& vec);
	void lookAt(float x, float y, float z);

	void normalizeUp();

	virtual void update() = 0;

  protected:

	Mat4f projection;
	Mat4f view;
	Mat4f projectionViewCombined;

	Vec3f position;
	Vec3f direction;
	Vec3f up;

	float near;
	float far;

	float viewportWidth;
	float viewportHeight;

	Vec3f cachedVector;
};


#endif // _BASE_CAMERA_H_

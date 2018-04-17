#ifndef _SCENE_2D_SHAPES_H_
#define _SCENE_2D_SHAPES_H_

#include "core/BaseScene.h"
#include "render/ShaderProgram.h"
#include "math/Vector3.h"

class BaseCamera;

class Scene2DShapes : public BaseScene
{
  public:

	explicit Scene2DShapes(Renderer& renderer) : BaseScene(renderer), shader(false, true, false), yaw(0.0f), pitch(0.0f), cameraDirectionToApply(Vec3f::ZERO) { }
	~Scene2DShapes();

	void onEnter() override;
	void onUpdate(int64_t microsecondsDelta) override;
	void onExit() override;

	void onKeyReleased(Key key) override;
	void onMouseMoved(int deltaX, int deltaY) override;

  private:

	void processInput(int64_t microsecondsDelta);

	ShaderProgram shader;
	BaseCamera* camera;
	float yaw;
	float pitch;
	Vec3f cameraDirectionToApply;

};

#endif
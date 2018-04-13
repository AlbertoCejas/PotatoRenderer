#ifndef _SCENE_2D_SHAPES_H_
#define _SCENE_2D_SHAPES_H_

#include "core/BaseScene.h"
#include "render/ShaderProgram.h"

class BaseCamera;

class Scene2DShapes : public BaseScene
{
  public:

	explicit Scene2DShapes(Renderer& renderer) : BaseScene(renderer), shader(false, true, 0) { }
	~Scene2DShapes();

	void onEnter() override;
	void onUpdate(int64_t microseconds) override;
	void onExit() override;

  private:

	ShaderProgram shader;
	BaseCamera* camera;
};

#endif
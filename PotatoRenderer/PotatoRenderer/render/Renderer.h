#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <cinttypes>
#include "render/ShapeRenderer.h"

class Window;
class Application;

class Renderer
{
  public:

	explicit Renderer();
	~Renderer();

	void init(Application* app);
	void update(int64_t microseconds);
	void render();

	inline ShapeRenderer& getShapeRenderer() { return shapeRenderer; }

  private:

	Window* window;
	Application* application;
	bool isInit;

	ShapeRenderer shapeRenderer;

};

#endif

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <cinttypes>
#include "render/ShapeRenderer.h"

class Window;
class Application;

class Renderer
{
  public:

	explicit Renderer(int width, int height);
	~Renderer();

	void init(Application* app);
	void update(int64_t microseconds);
	void beginRender() const;
	void render();
	void endRender() const;

	void pollEvents() const;

	inline const Window& getWindow() const { return *window; }
	inline ShapeRenderer& getShapeRenderer() { return *shapeRenderer; }
	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

  private:

	Window* window;
	Application* application;
	bool isInit;

	int32_t width;
	int32_t height;

	ShapeRenderer* shapeRenderer;

};

#endif

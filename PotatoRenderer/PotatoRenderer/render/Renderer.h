#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <cinttypes>

class Window;
class Application;

class Renderer
{
  public:

	explicit Renderer();
	~Renderer();

	void init(Application* app);
	void update(int32_t miliseconds);
	void render();

  private:

	bool isInit;
	Window* window;
	Application* application;
};

#endif

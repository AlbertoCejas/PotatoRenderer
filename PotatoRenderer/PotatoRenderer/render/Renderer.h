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
	void update(int64_t microseconds);
	void render();

  private:

	Window* window;
	Application* application;
	bool isInit;

};

#endif

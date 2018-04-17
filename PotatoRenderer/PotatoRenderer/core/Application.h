#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <cinttypes>
#include "render/Renderer.h"
#include "input/Keys.h"

class BaseScene;

class Application // TODO -> move input stuff to input system
{
  public:

	explicit Application();

	void init();
	void update(int64_t milisecs);

	inline bool mustExit() const { return this->exit; }
	inline void forceExit() { this->exit = true; }

  private:

	void initScenes();
	void switchToScene(int nextSceneIndex);

	void processInputEvents();
	void onKeyReleased(Key key);
	void onMouseMoved(int deltaX, int deltaY);

	int32_t currentSceneIndex;
	std::vector<BaseScene*> scenes;

	bool exit;
	Renderer renderer;
};

#endif
#ifndef _BASE_SCENE_H_
#define _BASE_SCENE_H_

#include <cstdint>
#include "input/Keys.h"

class Renderer;

class BaseScene
{
  public:

	explicit BaseScene(Renderer& _renderer) : renderer(_renderer) { }
	virtual ~BaseScene() { }

	virtual void onEnter() {}
	virtual void onUpdate(int64_t) {} // microseconds
	virtual void onExit() {}

	virtual void onKeyReleased(Key) { }
	virtual void onMouseMoved(int, int) {}   // deltaX, deltaY

  protected:

	Renderer& renderer;

};


#endif
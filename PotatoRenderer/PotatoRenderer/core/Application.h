#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <cinttypes>
#include "render/Renderer.h"

class Application
{
  public:

	explicit Application();

	void init();
	void update(int milisecs);
	void render();

	inline bool mustExit() const { return this->exit; }
	inline void forceExit() { this->exit = true; }

  private:

	bool exit;
	Renderer renderer;
};

#endif
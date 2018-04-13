#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <cinttypes>
#include "render/Renderer.h"

class BaseScene;

class Application
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

	int32_t currentSceneIndex;
	std::vector<BaseScene*> scenes;

	bool exit;
	Renderer renderer;
};

#endif
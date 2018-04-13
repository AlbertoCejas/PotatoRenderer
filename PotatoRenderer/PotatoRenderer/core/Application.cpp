#include "core/Application.h"
#include "core/BaseScene.h"
#include "scenes/Scene2DShapes.h"
#include <cassert>

Application::Application() : renderer(1024, 768), exit(false), currentSceneIndex(-1)
{

}

void Application::init()
{
	renderer.init(this);
	initScenes();
}

void Application::initScenes()
{
	Scene2DShapes* shapes = new Scene2DShapes(renderer);
	scenes.push_back(shapes);

	currentSceneIndex = 0;
	scenes[currentSceneIndex]->onEnter();
}

void Application::switchToScene(int nextSceneIndex)
{
	int numOfScenes = scenes.size();
	assert(nextSceneIndex > -1 && nextSceneIndex < numOfScenes);

	if (currentSceneIndex != -1)
	{
		scenes[currentSceneIndex]->onExit();
	}

	currentSceneIndex = nextSceneIndex;

	scenes[currentSceneIndex]->onEnter();
}

void Application::update(int64_t microseconds)
{
	renderer.pollEvents();

	BaseScene* scene = scenes[currentSceneIndex];
	scene->onUpdate(microseconds);
}
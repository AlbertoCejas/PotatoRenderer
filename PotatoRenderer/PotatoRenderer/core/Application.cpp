#include "core/Application.h"
#include "core/BaseScene.h"
#include "scenes/Scene2DShapes.h"
#include "input/InputSystem.h"
#include <cassert>
#include "render/Window.h"
#include "utils/FreeList.h"

struct hola
{
	int a;
	int b;
	int c;
};

Application::Application() : renderer(1024, 768), exit(false), currentSceneIndex(-1)
{

}

void Application::init()
{
	renderer.init(this);
	initScenes();
	InputSystem::setInputTarget(renderer.getWindow());
}

void Application::initScenes()
{
	Scene2DShapes* shapes = new Scene2DShapes(renderer);
	scenes.push_back(shapes);

	switchToScene(0);
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

	const Window& window = renderer.getWindow();

	if (window.requiresExit())
	{
		forceExit();
		return;
	}
	
	processInputEvents();

	BaseScene* scene = scenes[currentSceneIndex];
	scene->onUpdate(microseconds);
}


void Application::processInputEvents()
{
	InputEvent* inputEvent = InputSystem::popQueuedEvent();

	while (inputEvent != nullptr)
	{
		InputEventType type = inputEvent->type;

		switch (type)
		{
			case InputEventType::MOUSE_MOVE:
			{
				onMouseMoved(inputEvent->mouseMoveInfo.deltaX, inputEvent->mouseMoveInfo.deltaY);
				break;
			}

			case InputEventType::KEYBOARD_PRESS:
			{
				onKeyPressed(inputEvent->keyboardInfo.key);
				break;
			}

			case InputEventType::KEYBOARD_HOLD:
			{
				onKeyHold(inputEvent->keyboardInfo.key);
				break;
			}

			case InputEventType::KEYBOARD_RELEASE:
			{
				onKeyReleased(inputEvent->keyboardInfo.key);
				break;
			}

		}

		inputEvent = InputSystem::popQueuedEvent();
	}

	InputSystem::finishProcessingQueuedEvents();
}

void Application::onKeyPressed(Key key)
{
	BaseScene* scene = scenes[currentSceneIndex];
	scene->onKeyPressed(key);
}

void Application::onKeyHold(Key key)
{
	BaseScene* scene = scenes[currentSceneIndex];
	scene->onKeyHold(key);
}

void Application::onKeyReleased(Key key)
{
	if (key == Key::KEY_ESCAPE)
	{
		this->forceExit();
		return;
	}
	BaseScene* scene = scenes[currentSceneIndex];
	scene->onKeyReleased(key);
}

void Application::onMouseMoved(int deltaX, int deltaY)
{
	BaseScene* scene = scenes[currentSceneIndex];
	scene->onMouseMoved(deltaX, deltaY);
}
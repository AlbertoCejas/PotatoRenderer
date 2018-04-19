#include "input/InputSystem.h"
#include "render/Window.h"
#include <GLFW/glfw3.h>
#include <cassert>

FreeList<InputEvent> InputSystem::eventsPool(20u);
std::queue<InputEvent*> InputSystem::eventsQueueToProcess;
std::vector<InputEvent*> InputSystem::eventsToReturnToPool;
std::unordered_set<Key> InputSystem::pressedKeys;
int32_t InputSystem::lastXMousePos;
int32_t InputSystem::lastYMousePos;

void InputSystem::keyCallback(GLFWwindow*, int key, int, int action, int) // window, key, scancode, action, mods
{
	InputEvent* eventInstance = eventsPool.get();

	assert(eventInstance != nullptr);
	eventInstance->keyboardInfo.key = (Key)key;

	switch (action)
	{
		case GLFW_PRESS:
		{
			eventInstance->type = InputEventType::KEYBOARD_PRESS;
			pressedKeys.insert(Key(key));
			break;
		}

		case GLFW_RELEASE:
		{
			eventInstance->type = InputEventType::KEYBOARD_RELEASE;
			pressedKeys.erase(Key(key));
			break;
		}

		case GLFW_REPEAT:
		{
			eventInstance->type = InputEventType::KEYBOARD_HOLD;
			break;
		}
	}

	eventsQueueToProcess.push(eventInstance);
}

void InputSystem::mouseButtonCallback(GLFWwindow* window, int button, int action, int)// window, button, action, mods
{
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	InputEvent* eventInstance = eventsPool.get();

	assert(eventInstance != nullptr);
	eventInstance->mouseClickInfo.x = (int32_t)xPos;
	eventInstance->mouseClickInfo.y = (int32_t)yPos;
	eventInstance->mouseClickInfo.buttonId = button;

	switch (action)
	{
		case GLFW_PRESS:
			eventInstance->type = InputEventType::MOUSE_CLICK;
			break;

		case GLFW_RELEASE:
			eventInstance->type = InputEventType::MOUSE_RELEASE;
			break;
	}

	eventsQueueToProcess.push(eventInstance);
}

void InputSystem::mouseMoveCallback(GLFWwindow*, double xPos, double yPos)
{
	InputEvent* eventInstance = eventsPool.get();

	assert(eventInstance != nullptr);
	eventInstance->mouseMoveInfo.deltaX = (int32_t)xPos - lastXMousePos;
	eventInstance->mouseMoveInfo.deltaY = lastYMousePos - (int32_t)yPos;
	lastXMousePos = (int32_t)xPos;
	lastYMousePos = (int32_t)yPos;

	eventInstance->type = InputEventType::MOUSE_MOVE;
	eventsQueueToProcess.push(eventInstance);
}

void InputSystem::setInputTarget(const Window& window)
{
	GLFWwindow* windowPtr = &(window.getGLFWwindow());

	double xPos, yPos;
	glfwGetCursorPos(windowPtr, &xPos, &yPos);
	lastXMousePos = (int32_t)xPos;
	lastYMousePos = (int32_t)yPos;

	glfwSetKeyCallback(windowPtr, &InputSystem::keyCallback);
	glfwSetMouseButtonCallback(windowPtr, &InputSystem::mouseButtonCallback);
	glfwSetCursorPosCallback(windowPtr, &InputSystem::mouseMoveCallback);
}

InputEvent* InputSystem::popQueuedEvent()
{
	if (eventsQueueToProcess.empty())
	{
		return nullptr;
	}

	InputEvent* eventInstance = eventsQueueToProcess.front();

	eventsToReturnToPool.push_back(eventInstance);
	eventsQueueToProcess.pop();
	return eventInstance;
}

void InputSystem::finishProcessingQueuedEvents()
{
	for (InputEvent* inputEvent : eventsToReturnToPool)
	{
		eventsPool.free(*inputEvent);
	}

	eventsToReturnToPool.clear();
}

bool InputSystem::isKeyPressed(Key key)
{
	return pressedKeys.find(key) != pressedKeys.end();
}
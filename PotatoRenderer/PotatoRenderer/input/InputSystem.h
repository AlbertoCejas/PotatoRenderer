#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_

#include "utils/FreeList.h"
#include <cstdint>
#include "input/Keys.h"
#include <queue>

class Window;
struct GLFWwindow;

enum class InputEventType : int32_t { MOUSE_CLICK, MOUSE_RELEASE, MOUSE_MOVE, KEYBOARD_PRESS, KEYBOARD_HOLD, KEYBOARD_RELEASE };

struct MouseClickEventInfo
{
	int32_t x;
	int32_t y;
	int32_t buttonId;
};

struct MouseMoveEventInfo
{
	int32_t deltaX;
	int32_t deltaY;
};

struct KeyboardEventInfo
{
	Key key;
};

struct InputEvent
{
	InputEventType type;
	union
	{
		MouseClickEventInfo mouseClickInfo;
		MouseMoveEventInfo mouseMoveInfo;
		KeyboardEventInfo keyboardInfo;
	};
};

class InputSystem
{
  public:

	static void setInputTarget(const Window& window);
	static InputEvent* popQueuedEvent();
	static void finishProcessingQueuedEvents();

  private:

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void mouseMoveCallback(GLFWwindow* window, double xPos, double yPos);

	static int32_t lastXMousePos;
	static int32_t lastYMousePos;

	static FreeList<InputEvent> eventsPool;
	static std::queue<InputEvent*> eventsQueueToProcess;
	static std::vector<InputEvent*> eventsToReturnToPool;
};

#endif
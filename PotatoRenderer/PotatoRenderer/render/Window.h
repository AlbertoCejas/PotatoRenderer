#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <cinttypes>

struct GLFWwindow;

class Window
{
  public:

	Window(const char* title, int width, int height);

	bool requiresExit() const;

	void swapBuffers();

  private:

	GLFWwindow* window;
};

#endif
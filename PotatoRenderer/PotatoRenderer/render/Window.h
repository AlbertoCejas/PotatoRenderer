#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <cinttypes>

class GLFWwindow;

class Window
{
  public:

	explicit Window(const char* title, int32_t width, int32_t height);

	bool requiresExit() const;

	void swapBuffers();

  private:

	GLFWwindow* window;
};

#endif
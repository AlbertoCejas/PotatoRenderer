#include "Window.h"
#include <GLFW/glfw3.h>

Window::Window(const char* title, int width, int height)
{
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(window);
}

bool Window::requiresExit() const
{
	return glfwWindowShouldClose(window) != 0u;
}

void Window::swapBuffers()
{
	// Swap the screen buffers
	glfwSwapBuffers(window);
}
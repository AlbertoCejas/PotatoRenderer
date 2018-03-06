#include "Window.h"
#include <GLFW/glfw3.h>

Window::Window(const char* title, int32_t width, int32_t height)
{
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(window);
}

bool Window::requiresExit() const
{
	return glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
	// Swap the screen buffers
	glfwSwapBuffers(window);
}
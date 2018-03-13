#include "Renderer.h"
#include "core/Application.h"
#include <cassert>

#include "Window.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

Renderer::Renderer() : application(nullptr), window(nullptr), isInit(false)
{

}

Renderer::~Renderer()
{
	delete window;
	glfwTerminate();
}

void Renderer::init(Application* app)
{
	assert(isInit == false);

	this->application = app;

	int32_t width = 1024;
	int32_t height = 768;

	// Init GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.X
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL X.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // No compatibility context, new OpenGL with CORE_PROFILE
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = new Window("RendererSample", width, height);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, width, height);

	isInit = true;
}

void Renderer::update(int64_t)
{
	if (window->requiresExit())
	{
		application->forceExit();
	}

}

void Renderer::render()
{
	// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
	glfwPollEvents();

	// Render
	// Clear the colorbuffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);



	window->swapBuffers();
}
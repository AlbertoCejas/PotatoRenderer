#include "Application.h"

Application::Application() : exit(false)
{

}

void Application::init()
{
	renderer.init(this);
}

void Application::update(int64_t microseconds)
{
	renderer.update(microseconds);
}

void Application::render()
{
	renderer.render();
}
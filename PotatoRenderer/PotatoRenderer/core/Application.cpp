#include "Application.h"

Application::Application() : exit(false)
{

}

void Application::init()
{
	renderer.init(this);
}

void Application::update(int miliseconds)
{
	renderer.update(miliseconds);
}

void Application::render()
{
	renderer.render();
}
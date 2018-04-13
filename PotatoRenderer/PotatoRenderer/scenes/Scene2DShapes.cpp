#include "scenes/Scene2DShapes.h"
#include "render/PerspectiveCamera.h"
#include "render/Renderer.h"
#include "render/ShapeRenderer.h"

Scene2DShapes::~Scene2DShapes()
{
	delete camera;
}

void Scene2DShapes::onEnter()
{
	camera = new PerspectiveCamera((float)renderer.getWidth(), (float)renderer.getHeight());
	camera->translate(0, 0, 50);
	camera->update();
}

void Scene2DShapes::onUpdate(int64_t) // microseconds
{
	ShapeRenderer& shapeRenderer = renderer.getShapeRenderer();

	renderer.beginRender();
	{
		shapeRenderer.begin(*camera, DrawMode::FILLED);
		{
			shapeRenderer.triangle
			(
			    0.0f, 0.0f, 0.0f,
			    50.0f, 0.0f, 0.0f,
			    25.0f, 50.0f, 0.0f,
			    Color::BLUE
			);
			shapeRenderer.rectangle
			(
			    -10.0f, 20.0f, 0.0f,
			    -30.0f, 20.0f, 0.0f,
			    -30.0f, 40.0f, 0.0f,
			    -10.0f, 40.0f, 0.0f,
			    Color::ORANGE
			);
			shapeRenderer.circle(0.0f, 0.0f, 0.0f, 5.0f, 20, Color::PINK);
		}
		shapeRenderer.end();


		shapeRenderer.begin(*camera, DrawMode::LINES);
		{
			shapeRenderer.triangle
			(
			    0.0f, 0.0f, 10.0f,
			    -50.0f, 0.0f, 10.0f,
			    -25.0f, 50.0f, 10.0f,
			    Color::ORANGE
			);
			shapeRenderer.rectangle
			(
			    10.0f, 20.0f, 0.0f,
			    30.0f, 20.0f, 0.0f,
			    30.0f, 40.0f, 0.0f,
			    10.0f, 40.0f, 0.0f,
			    Color::ORANGE
			);
			shapeRenderer.line
			(
			    0.0f, -10.0f, 0.0f,
			    10.0f, -10.0f, 0.0f,
			    Color::PINK
			);
		}

		shapeRenderer.end();
	}
	renderer.endRender();
}

void Scene2DShapes::onExit()
{

}
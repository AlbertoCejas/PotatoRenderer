#include "render/PerspectiveCamera.h"
#include "render/Renderer.h"
#include "render/ShapeRenderer.h"
#include "scenes/Scene2DShapes.h"
#include "input/InputSystem.h"

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

void Scene2DShapes::onUpdate(int64_t microsecondsDelta)
{
	processInput(microsecondsDelta);

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

void Scene2DShapes::onKeyPressed(Key key)
{
	cameraDirectionToApply += getCameraDirection(key);
}

void Scene2DShapes::onKeyReleased(Key key)
{
	cameraDirectionToApply -= getCameraDirection(key);
}

void Scene2DShapes::onMouseMoved(int deltaX, int deltaY)
{
	float sentitivity = 0.25f;

	yaw += (deltaX * sentitivity);
	pitch += (deltaY * sentitivity);

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}
}

void Scene2DShapes::processInput(int64_t microsecondsDelta)
{
	bool requiresCameraUpdate = false;

	if (yaw != 0.0f || pitch != 0.0f)
	{
		Vector3<float> right(camera->getDirection());
		right.cross(camera->getUp()).normalize();

		//Vec3f direction(camera->getDirection());
		//Vec3f right(camera.getDirection());
		//right.cross(camera.getUp());
		//right.normalize();
		camera->rotateDegrees(right.x, right.y, right.z, pitch);
		camera->rotateDegrees(0.0f, 1.0f, 0.0f, -yaw); // This should be the updated UP vector of the camera
		
		yaw = 0.0f;
		pitch = 0.0f;
		requiresCameraUpdate = true;

		updateInputDirection();
	}

	if (cameraDirectionToApply != Vec3f::ZERO)
	{
		float speed = 50.0f; // units per second
		float translation = speed * microsecondsDelta / 1000000.0f;
		Vec3f cameraDirectionToApplyCopy(cameraDirectionToApply);
		cameraDirectionToApplyCopy.normalize();
		camera->translate(cameraDirectionToApplyCopy * translation);
		requiresCameraUpdate = true;
	}

	if (requiresCameraUpdate)
	{
		camera->update();
	}
}

Vec3f Scene2DShapes::getCameraDirection(Key key)
{
	Vector3<float> right(camera->getDirection());
	right.cross(camera->getUp()).normalize();

	switch (key)
	{
		case Key::KEY_W:
		{
			return camera->getDirection();
		}

		case Key::KEY_S:
		{
			return -camera->getDirection();
		}

		case Key::KEY_D:
		{
			return right;
		}

		case Key::KEY_A:
		{
			return -right;
		}
	}

	return Vec3f::ZERO;
}

void Scene2DShapes::updateInputDirection()
{
	cameraDirectionToApply.set(Vec3f::ZERO);

	if (InputSystem::isKeyPressed(Key::KEY_W))
	{
		cameraDirectionToApply += getCameraDirection(Key::KEY_W);
	}
	if (InputSystem::isKeyPressed(Key::KEY_S))
	{
		cameraDirectionToApply += getCameraDirection(Key::KEY_S);
	}
	if (InputSystem::isKeyPressed(Key::KEY_D))
	{
		cameraDirectionToApply += getCameraDirection(Key::KEY_D);
	}
	if (InputSystem::isKeyPressed(Key::KEY_A))
	{
		cameraDirectionToApply += getCameraDirection(Key::KEY_A);
	}

}
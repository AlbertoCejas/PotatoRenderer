#include "render/PerspectiveCamera.h"
#include "render/Renderer.h"
#include "render/ShapeRenderer.h"
#include "scenes/Scene2DSprites.h"
#include "input/InputSystem.h"
#include "render/Texture.h"

Scene2DSprites::Scene2DSprites(Renderer& renderer) : BaseScene(renderer), shader(false, true, false), yaw(0.0f), pitch(0.0f), cameraDirectionToApply(Vec3f::ZERO), spriteBatch(1000) 
{
	boxTexture = new Texture("assets/texture.jpg");
	boxTextureRegion = new TextureRegion(*boxTexture);
	boxSprite = new Sprite(*boxTextureRegion);
}

Scene2DSprites::~Scene2DSprites()
{
	delete camera;
	delete boxSprite;
	delete boxTextureRegion;
	delete boxTexture;
}

void Scene2DSprites::onEnter()
{
	camera = new PerspectiveCamera((float)renderer.getWidth(), (float)renderer.getHeight());
	camera->translate(0, 0, 50);
	camera->update();

}

void Scene2DSprites::onUpdate(int64_t microsecondsDelta)
{
	processInput(microsecondsDelta);

	renderer.beginRender();
	{
		spriteBatch.begin(*camera);
		{
			spriteBatch.render(*boxSprite);
		}
		spriteBatch.end();
	}
	renderer.endRender();
}

void Scene2DSprites::onExit()
{

}

void Scene2DSprites::onKeyPressed(Key key)
{
	cameraDirectionToApply += getCameraDirection(key);
}

void Scene2DSprites::onKeyReleased(Key key)
{
	cameraDirectionToApply -= getCameraDirection(key);
}

void Scene2DSprites::onMouseMoved(int deltaX, int deltaY)
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

void Scene2DSprites::processInput(int64_t microsecondsDelta)
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

Vec3f Scene2DSprites::getCameraDirection(Key key)
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

void Scene2DSprites::updateInputDirection()
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
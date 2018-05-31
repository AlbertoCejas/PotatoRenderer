#ifndef _SCENE_2D_SPRITES_H_
#define _SCENE_2D_SPRITES_H_

#include "core/BaseScene.h"
#include "render/ShaderProgram.h"
#include "math/Vector3.h"
#include "render/SpriteBatch.h"

class BaseCamera;
class Texture;
class TextureRegion;
class Sprite;

class Scene2DSprites : public BaseScene
{
public:

	explicit Scene2DSprites(Renderer& renderer);
	~Scene2DSprites();

	void onEnter() override;
	void onUpdate(int64_t microsecondsDelta) override;
	void onExit() override;

	void onKeyPressed(Key key) override;
	void onKeyReleased(Key key) override;
	void onMouseMoved(int deltaX, int deltaY) override;

private:

	void processInput(int64_t microsecondsDelta);
	Vec3f getCameraDirection(Key key);
	void updateInputDirection();

	ShaderProgram shader;
	BaseCamera* camera;
	float yaw;
	float pitch;
	Vec3f cameraDirectionToApply;

	SpriteBatch spriteBatch;
	Texture* boxTexture;
	TextureRegion* boxTextureRegion;
	Sprite* boxSprite;

};

#endif
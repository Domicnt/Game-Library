#include "object.h"

Object::Object(b2Body* Body)
{
	body = Body;
	currentTexture = -1;
	currentAnimation = -1;
	textureHeight = 1;
	textureWidth = 1;
}

void Object::draw(const Graphics& sdl2)
{
	const auto bodyPoint = body->GetWorldCenter();
	const auto center = sdl2.camera.projectPoint({ int(bodyPoint.x), int(bodyPoint.y)});
	if(currentTexture != -1)
	{
		sdl2.drawImageEx(center.x - textureWidth / 2, center.y - textureHeight / 2, textureWidth, textureHeight, textures[currentTexture], body->GetAngle() * 180 / 3.14159, { textureWidth / 2, textureHeight / 2 });
	}
	else if (currentAnimation != -1)
	{
		//update position and render
		animations[currentAnimation].pos = {center.x - animations[currentAnimation].w / 2, center.y - animations[currentAnimation].h / 2};
		animations[currentAnimation].angle = body->GetAngle() * 180 / 3.14159;
		animations[currentAnimation].draw(sdl2.renderer);
	}
}

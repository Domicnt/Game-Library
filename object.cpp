#include "object.h"

Object::Object(b2Body* Body)
{
	body = Body;
	currentTexture = -1;
	currentAnimation = -1;
	textureHeight = 1;
	textureWidth = 1;
}

void Object::draw(const Graphics& graphics)
{
	if (!graphics.camera.b2BodyVisible(body))
		return;
	const auto bodyPoint = body->GetWorldCenter();
	const auto center = graphics.camera.projectPoint(bodyPoint.x, bodyPoint.y);
	if(currentTexture != -1)
	{
		graphics.drawImageEx(1 + center.x - textureWidth / 2, 1 + center.y - textureHeight / 2, textureWidth, textureHeight, textures[currentTexture], body->GetAngle() * 180 / 3.14159);
	}
	else if (currentAnimation != -1)
	{
		//update position and render
		animations[currentAnimation].pos = {1 + center.x - animations[currentAnimation].w / 2, 1 + center.y - animations[currentAnimation].h / 2};
		animations[currentAnimation].angle = body->GetAngle() * 180 / 3.14159;
		animations[currentAnimation].draw(graphics.renderer, graphics.camera);
	}
}

#pragma once

#include "graphics.h"
#include "physics.h"
#include "animation.h"

class Object
{
public:
	//physics body of the object
	b2Body* body;
	//vector of static textures for the object
	std::vector<SDL_Texture*> textures;
	//vector of animations
	std::vector<Animation> animations;

	//current texture, set to -1 if no current texture
	int currentTexture;
	//current animation, set to -1 if no curren animation
	int currentAnimation;

	//texture dimensions, used to find center
	int textureWidth, textureHeight;
	//body dimensions
	//float bodyWidth, bodyHeight;

	Object() = default;
	Object(b2Body* Body);

	//draw texture/animation
	void draw(const Graphics& graphics);
};
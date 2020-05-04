#pragma once

#include "graphics.h"

class Animation
{
public:
	//position
	SDL_FPoint pos;
	//dimensions
	int w, h;

	//center of the target location
	SDL_Point center;
	//angle of the animation
	float angle;

	//dimensions of the sprite sheet
	int sheetW, sheetH;
	//dimensions of a single frame
	int frameW, frameH;

	//total amount of frames
	int frames;
	//current frame
	int frame;

	//if the animation shoul repeat
	bool repeat;
	//if the animation is paused
	bool pause;

	//texture of the sprite sheet
	SDL_Texture* texture;

	//frames per second that the animation should run at
	float framesPerSecond;
	//last time the animation advanced to the next frame
	double lastAnimationStep;

	//constructor
	Animation(const int& X, const int& Y, const int& W, const int& H, SDL_Texture* Texture, const int& SheetW, const int& SheetH, const int& FrameW, const int& FrameH, const int& Frames);

	//draws a frame and advances to the next, returns false if it has reached the last frame
	bool draw(SDL_Renderer* renderer);
};
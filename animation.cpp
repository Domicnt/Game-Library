#include "animation.h"

#include "clock.h"

Animation::Animation(const int& X, const int& Y, const int& W, const int& H, SDL_Texture* Texture, const int& SheetW, const int& SheetH, const int& FrameW, const int& FrameH, const int& Frames)
{
	pos = { X, Y };
	w = W;
	h = H;
	angle = 0;
	sheetW = SheetW;
	sheetH = SheetH;
	frameW = FrameW;
	frameH = FrameH;
	center = { w / 2, h / 2 };
	frame = 0;
	frames = Frames;
	repeat = false;
	pause = false;
	texture = Texture;
	framesPerSecond = 12;
	lastAnimationStep = Clock::checkTime();
}

bool Animation::draw(SDL_Renderer* renderer, Camera camera)
{
	//current frame * frame width / total width
	int row = floor(frame * frameW / sheetW);
	//current frame * frame width % total width
	const auto srcX = frame * frameW % sheetW;
	//row * frame height
	const auto srcY = row * frameH;
	//draw to renderer
	SDL_Rect dstrect = { pos.x + w / 2 - w * camera.zoom / 2, pos.y + h / 2 - h * camera.zoom / 2, w * camera.zoom, h * camera.zoom };
	SDL_Rect srcrect = { srcX, srcY, frameW, frameH };
	SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, angle, nullptr, SDL_FLIP_NONE);
	//increment frame if not paused
	if (lastAnimationStep + 1000 / framesPerSecond <= Clock::checkTime()) {
		lastAnimationStep = Clock::checkTime();
		if (!pause) frame++;
	}
	//return false/restart if it has played all frames
	if (frame >= frames)
	{
		if (!repeat) {
			return false;
		}
		frame = 0;
		row = 0;
	}
	return true;
}
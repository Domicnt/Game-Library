#pragma once
#include "vcpkg/installed/x86-windows/include/SDL2/SDL.h"
#include "vcpkg/installed/x86-windows/include/SDL2/SDL_image.h"
#include "vcpkg/installed/x86-windows/include/SDL2/SDL_ttf.h"

#include "camera.h"

class Graphics
{
public:
	//identification of the window
	SDL_Window* window;
	//collection of everything drawn, can be rendered to window
	SDL_Renderer* renderer;
	//rgb of the background, each is between 1 and 255
	Uint8 r, g, b;

	//camera for rendering
	Camera camera;
};

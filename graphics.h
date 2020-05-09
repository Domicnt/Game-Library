#pragma once
#include "vcpkg/installed/x86-windows/include/SDL2/SDL.h"
#include "vcpkg/installed/x86-windows/include/SDL2/SDL_image.h"
#include "vcpkg/installed/x86-windows/include/SDL2/SDL_ttf.h"

#include <string>

#include "camera.h"
#include "clock.h"

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

	//font for rendered text
	TTF_Font* font;

	SDL_Texture* fpsTexture;

	//constructor, takes desired width and height of window
	Graphics(const int& width, const int& height);

	//Functions for rendering geometry:
	
	void drawLine(const int& x1, const int& y1, const int& x2, const int& y2) const;
	void drawRect(const int& x1, const int& y1, const int& x2, const int& y2) const;
	void fillRect(const int& x1, const int& y1, const int& x2, const int& y2) const;
	void drawCircle(const int& x, const int& y, const int& r) const;
	void fillCircle(const int& x, const int& y, const int& r) const;
	
	//Functions for rendering text:

	void loadFont(const std::string& path, const int& size);
	SDL_Texture* loadTTFTexture(const std::string& text, const SDL_Color& color) const;
	void drawFPS(Clock clock, const SDL_Rect& dstRect);
	
	//Functions for rendering images:

	SDL_Texture* loadTexture(const std::string& path) const;
	void drawImage(const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture, const bool& scaling) const;
	void drawImageEx(const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture, const double& angle, const bool& scaling) const;
	void drawPartialImage(const int& textureX, const int& textureY, const int& textureW, const int& textureH, const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture, const bool& scaling) const;
	void drawPartialImageEx(const int& textureX, const int& textureY, const int& textureW, const int& textureH, const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture, const double& angle, const bool& scaling) const;

	//Render everything to the window, and clear renderer
	void render() const;
};

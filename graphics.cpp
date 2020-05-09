#include "graphics.h"

Graphics::Graphics(const int& width, const int& height)
{
	//initialize SDL and libraries
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	//set image scaling quality
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	//create window and renderer
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);// | SDL_RENDERER_PRESENTVSYNC); // v-sync

	//Camera
	camera = { width,height,20 };

	//define draw settings
	r = 255;
	g = 255;
	b = 255;

	loadFont("../Game-Library/font.ttf", 12);
}

void Graphics::drawLine(const int& x1, const int& y1, const int& x2, const int& y2) const
{
	//check if it could be visible
	if (camera.visible({ x1, y1 }) || camera.visible({ x2, y2 }) || camera.visible({ x1, y2 }) || camera.visible({ x2, y1 }))
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Graphics::drawRect(const int& x1, const int& y1, const int& x2, const int& y2) const
{
	//check if it could be visible
	if (camera.visible({ x1, y1 }) || camera.visible({ x2, y2 }) || camera.visible({ x1, y2 }) || camera.visible({ x2, y1 }))
	{
		SDL_Rect rect = { x1, y1, x2 - x1, y2 - y1 };
		SDL_RenderDrawRect(renderer, &rect);
	}
}

void Graphics::fillRect(const int& x1, const int& y1, const int& x2, const int& y2) const
{
	//check if either opposite corner is visible
	if (camera.visible({ x1, y1 }) || camera.visible({ x2, y2 }) || camera.visible({ x1, y2 }) || camera.visible({ x2, y1 }))
	{
		SDL_Rect rect = { x1, y1, x2 - x1, y2 - y1 };
		SDL_RenderFillRect(renderer, &rect);
	}
}

void Graphics::drawCircle(const int& x, const int& y, const int& r) const
{
	if (camera.visible({ x - r, y - r }) || camera.visible({ x + r, y + r }) || camera.visible({ x - r, y + r }) || camera.visible({ x + r, y - r }))
	{
		const auto diameter = r * 2;

		auto diffX = r - 1;
		auto diffY = 0;
		auto tx = 1;
		auto ty = 1;
		auto error = tx - diameter;

		while (x >= y)
		{
			SDL_RenderDrawPoint(renderer, x + diffX, y - diffY);
			SDL_RenderDrawPoint(renderer, x + diffX, y + diffY);
			SDL_RenderDrawPoint(renderer, x - diffX, y - diffY);
			SDL_RenderDrawPoint(renderer, x - diffX, y + diffY);
			SDL_RenderDrawPoint(renderer, x + diffY, y - diffX);
			SDL_RenderDrawPoint(renderer, x + diffY, y + diffX);
			SDL_RenderDrawPoint(renderer, x - diffY, y - diffX);
			SDL_RenderDrawPoint(renderer, x - diffY, y + diffX);

			if (error <= 0)
			{
				++diffY;
				error += ty;
				ty += 2;
			}

			if (error > 0)
			{
				--diffX;
				tx += 2;
				error += (tx - diameter);
			}
		}
	}
}

void Graphics::fillCircle(const int& x, const int& y, const int& r) const
{
	if (camera.visible({ x - r, y - r }) || camera.visible({ x + r, y + r }) || camera.visible({ x - r, y + r }) || camera.visible({ x + r, y - r }))
	{
		const auto diameter = r * 2;

		auto diffX = r - 1;
		auto diffY = 0;
		auto tx = 1;
		auto ty = 1;
		auto error = tx - diameter;

		while (x >= y)
		{
			//  Each of the following renders an octant of the circle
			fillRect(x + diffX, y - diffY, x, y);
			fillRect(x + diffX, y + diffY, x, y);
			fillRect(x - diffX, y - diffY, x, y);
			fillRect(x - diffX, y + diffY, x, y);
			fillRect(x + diffY, y - diffX, x, y);
			fillRect(x + diffY, y + diffX, x, y);
			fillRect(x - diffY, y - diffX, x, y);
			fillRect(x - diffY, y + diffX, x, y);

			if (error <= 0)
			{
				++diffY;
				error += ty;
				ty += 2;
			}

			if (error > 0)
			{
				--diffX;
				tx += 2;
				error += (tx - diameter);
			}
		}
	}
}

void Graphics::loadFont(const std::string& path, const int& size)
{
	font = TTF_OpenFont(path.c_str(), size);
	if (font == nullptr) {
		printf("Unable to load font %s. Error message: %s\n", path.c_str(), TTF_GetError());
	}
}

SDL_Texture* Graphics::loadTTFTexture(const std::string& text, const SDL_Color& color) const
{
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	//Create texture from surface
	newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	//Get rid of old loaded surface
	SDL_FreeSurface(textSurface);
	return newTexture;
}

void Graphics::drawFPS(Clock clock, const SDL_Rect& dstRect)
{
	if(!fpsTexture || clock.updateTime())
	{
		//destroys texture if it exists
		if (!!fpsTexture)
			SDL_DestroyTexture(fpsTexture);
		//load new texture
		const auto tempFont = font;
		loadFont("../Game-Library/font.ttf", 20);
		fpsTexture = loadTTFTexture(std::to_string(clock.fps), { 0,0,0,255 });
		font = tempFont;
	}
	drawImage(dstRect.x, dstRect.y, dstRect.w, dstRect.h, fpsTexture, false);
}

SDL_Texture* Graphics::loadTexture(const std::string& path) const
{
	SDL_Texture* newTexture = nullptr;
	//Load image at specified path
	SDL_Surface* newSurface = IMG_Load(path.c_str());
	if (newSurface == nullptr) {
		printf("Unable to load image %s. Error message: %s\n", path.c_str(), IMG_GetError());
		return nullptr;
	}
	//Create texture from surface
	newTexture = SDL_CreateTextureFromSurface(renderer, newSurface);
	//Get rid of old loaded surface
	SDL_FreeSurface(newSurface);
	return newTexture;
}

void Graphics::drawImage(const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture, const bool& scaling) const
{
	//the rect of the place on the screen where the image should be drawn
	SDL_Rect dstrect;
	if (scaling)
		dstrect = { int(x + w / 2 - w * camera.zoom / 2), int(y + h / 2 - h * camera.zoom / 2), int(w * camera.zoom), int(h * camera.zoom) };
	else
		dstrect = { x, y, w, h };
	SDL_RenderCopy(renderer, texture, nullptr, &dstrect);
}

void Graphics::drawImageEx(const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture, const double& angle, const bool& scaling) const
{
	//the rect of the place on the screen where the image should be drawn
	SDL_Rect dstrect;
	if (scaling)
		dstrect = { int(x + w / 2 - w * camera.zoom / 2), int(y + h / 2 - h * camera.zoom / 2), int(w * camera.zoom), int(h * camera.zoom) };
	else
		dstrect = { x, y, w, h };	SDL_RenderCopyEx(renderer, texture, nullptr, &dstrect, angle, nullptr, SDL_FLIP_NONE);
}

void Graphics::drawPartialImage(const int& textureX, const int& textureY, const int& textureW, const int& textureH, const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture, const bool& scaling) const
{
	//the rect of the place on the screen where the image should be drawn
	SDL_Rect dstrect;
	if (scaling)
		dstrect = { int(x + w / 2 - w * camera.zoom / 2), int(y + h / 2 - h * camera.zoom / 2), int(w * camera.zoom), int(h * camera.zoom) };
	else
		dstrect = { x, y, w, h };	//the rect of the place on the texture from which the image should be taken
	SDL_Rect srcrect = { textureX, textureY, textureW, textureH };
	SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
}

void Graphics::drawPartialImageEx(const int& textureX, const int& textureY, const int& textureW, const int& textureH, const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture, const double& angle, const bool& scaling) const
{
	//the rect of the place on the screen where the image should be drawn
	SDL_Rect dstrect;
	if (scaling)
		dstrect = { int(x + w / 2 - w * camera.zoom / 2), int(y + h / 2 - h * camera.zoom / 2), int(w * camera.zoom), int(h * camera.zoom) };
	else
		dstrect = { x, y, w, h };	//the rect of the place on the texture from which the image should be taken
	SDL_Rect srcrect = { textureX, textureY, textureW, textureH };
	SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, angle, nullptr, SDL_FLIP_NONE);
}

void Graphics::render() const
{
	//temporarily store current draw color and alpha
	Uint8 tempR, tempG, tempB, tempA;
	SDL_GetRenderDrawColor(renderer, &tempR, &tempG, &tempB, &tempA);
	//render whatever was drawn to the renderer
	SDL_RenderPresent(renderer);
	//clear the renderer
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderClear(renderer);
	//reset old draw color
	SDL_SetRenderDrawColor(renderer, tempR, tempG, tempB, tempA);
}
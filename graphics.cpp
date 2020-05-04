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
	camera = { 0,0,width,height,1 };
	
	//define draw settings
	r = 255;
	g = 255;
	b = 255;
}

void Graphics::drawLine(const int& x1, const int& y1, const int& x2, const int& y2) const
{
	//check if it could be visible
	if (camera.visible({x1, y1}) || camera.visible({x2, y2}) || camera.visible({x1, y2}) || camera.visible({x2, y1}))
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Graphics::drawRect(const int& x1, const int& y1, const int& x2, const int& y2) const
{
	//check if it could be visible
	if (camera.visible({ x1, y1 }) || camera.visible({ x2, y2 }) || camera.visible({x1, y2}) || camera.visible({x2, y1}))
	{
		SDL_Rect rect = {x1, y1, x2 - x1, y2 - y1};
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
	if (camera.visible({ x - r, y - r }) || camera.visible({ x + r, y + r }) || camera.visible({x - r, y + r}) || camera.visible({x + r, y - r}))
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

void Graphics::drawImage(const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture) const
{
	//the rect of the place on the screen where the image should be drawn
	SDL_Rect dstrect = { x, y, w, h };
	if (camera.visible({x, y}) || camera.visible({ x + w, y + h }) || camera.visible({ x, y + h }) || camera.visible({ x + w, y }))
		SDL_RenderCopy(renderer, texture, nullptr, &dstrect);
}

void Graphics::drawImageEx(const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture, const double& angle, const SDL_Point& center) const
{
	//the rect of the place on the screen where the image should be drawn
	SDL_Rect dstrect = { x, y, w, h };
	//diagonal radius of a square, to test if one would be on screen, even rotated
	const auto d = sqrt(2) / 2;
	if (camera.visible({ int(x - w * d), int(y - h * d) }) || camera.visible({ int(x + w + w * d), int(y + h + h * d) }) || camera.visible({ int(x - w * d), int(y + h + h * d) }) || camera.visible({ int(x + w + w * d), int(y - h * d) }))
		SDL_RenderCopyEx(renderer, texture, nullptr, &dstrect, angle, &center, SDL_FLIP_NONE);
}

void Graphics::drawPartialImage(const int& textureX, const int& textureY, const int& textureW, const int& textureH, const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture) const
{
	//the rect of the place on the screen where the image should be drawn
	SDL_Rect dstrect = { x, y, w, h };
	if (camera.visible({ x, y }) || camera.visible({ x + w, y + h }) || camera.visible({ x, y + h }) || camera.visible({ x + w, y }))
	{
		//the rect of the place on the texture from which the image should be taken
		SDL_Rect srcrect = { textureX, textureY, textureW, textureH };
		SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
	}
}

void Graphics::drawPartialImageEx(const int& textureX, const int& textureY, const int& textureW, const int& textureH, const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture, const double& angle, const SDL_Point& center) const
{
	//the rect of the place on the screen where the image should be drawn
	SDL_Rect dstrect = { x, y, w, h };
	//diagonal radius of a square, to test if one would be on screen, even rotated
	const auto d = sqrt(2) / 2;
	if (camera.visible({ int(x - w * d), int(y - h * d) }) || camera.visible({ int(x + w + w * d), int(y + h + h * d) }) || camera.visible({ int(x - w * d), int(y + h + h * d) }) || camera.visible({ int(x + w + w * d), int(y - h * d) }))
	{
		//the rect of the place on the texture from which the image should be taken
		SDL_Rect srcrect = { textureX, textureY, textureW, textureH };
		SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, angle, &center, SDL_FLIP_NONE);
	}
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
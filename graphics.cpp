#include "graphics.h"

Graphics::Graphics(const int& width, const int& height)
{
}

void Graphics::drawLine(const int& x1, const int& y1, const int& x2, const int& y2) const
{
}

void Graphics::drawRect(const int& x1, const int& y1, const int& x2, const int& y2) const
{
}

void Graphics::fillRect(const int& x1, const int& y1, const int& x2, const int& y2) const
{
}

void Graphics::drawCircle(const int& x, const int& y, const int& r) const
{
}

void Graphics::fillCircle(const int& x, const int& y, const int& r) const
{
}

void Graphics::loadFont(const std::string& path, const int& size)
{
}

SDL_Texture* Graphics::loadTTFTexture(const std::string& text, const SDL_Color& color)
{
	return nullptr;
}

SDL_Texture* Graphics::loadTexture(const std::string& path)
{
	return nullptr;
}

void Graphics::drawImage(const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture) const
{
}

void Graphics::drawImageEx(const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture, const double& angle, const SDL_Point& center) const
{
}

void Graphics::drawPartialImage(const int& textureX, const int& textureY, const int& textureW, const int& textureH, const int& x, const int& y, const int& w, const int& h, SDL_Texture* texture) const
{
}

void Graphics::render() const
{
}

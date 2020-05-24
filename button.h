#pragma once

#include "graphics.h"
#include "input.h"

class Button
{
public:
	//position and size
	int x, y, w, h;

	//if mouse is hovering over the button
	bool hover;

	SDL_Texture* texture;
	SDL_Texture* hoverTexture;

	//constructors
	Button();
	Button(const int& X, const int& Y, const int& W, const int& H);
	Button(const int& X, const int& Y, const int& W, const int& H, Graphics& graphics, std::string str);
	Button(const int& X, const int& Y, const int& W, const int& H, SDL_Texture* Texture, SDL_Texture* HoverTexture);
	
	//returns if the button was pressed
	bool update(Input& input, Graphics& graphics);
	//draws button, texture if applicable
	void draw(Graphics graphics) const;
};
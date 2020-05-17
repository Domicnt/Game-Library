#pragma once
#include "graphics.h"
#include "input.h"
#include "button.h"
#include <vector>

class Menu
{
public:
	//vector of buttons
	std::vector<Button> buttons;

	//position and dimensions of background image
	int x, y, w, h;
	//background image
	SDL_Texture* texture;
	
	//constructor
	Menu();
	Menu(const int& X, const int& Y, const int& W, const int& H, SDL_Texture* Texture);
	
	//returns which button was pressed, else 0
	int update(Input input);
	//draws all buttons over background texture
	void draw(Graphics graphics);
};

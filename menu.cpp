#include "menu.h"

Menu::Menu()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	texture = nullptr;
}

Menu::Menu(const int& X, const int& Y, const int& W, const int& H, SDL_Texture* Texture)
{
	x = X;
	y = Y;
	w = W;
	h = H;
	texture = Texture;
}

int Menu::update(Input input)
{
	auto buttonPressed = 0;
	for (auto i = 0; i < std::size(buttons); i++)
	{
		if (buttons[i].update(input))
			buttonPressed = i + 1;
	}
	return buttonPressed;
}

void Menu::draw(Graphics graphics)
{
	if (texture)
		graphics.drawImage(x, y, w, h, texture, false);
	for (auto& i : buttons)
	{
		i.draw(graphics);
	}
}

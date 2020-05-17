#include "button.h"
#include "functions.h"

Button::Button()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	hover = false;
	texture = nullptr;
	hoverTexture = nullptr;
}

Button::Button(const int& X, const int& Y, const int& W, const int& H)
{
	x = X;
	y = Y;
	w = W;
	h = H;
	hover = false;
	texture = nullptr;
	hoverTexture = nullptr;
}

Button::Button(const int& X, const int& Y, const int& W, const int& H, SDL_Texture* Texture, SDL_Texture* HoverTexture)
{
	x = X;
	y = Y;
	w = W;
	h = H;
	hover = false;
	texture = Texture;
	hoverTexture = HoverTexture;
}

bool Button::update(Input input)
{
	const auto pos = Input::getPos();
	hover = Functions::rectVsRect(x, y, w, h, pos.x, pos.y, 0, 0);
	return hover && input.leftButton;
}

void Button::draw(Graphics graphics) const
{
	//if mouse is not over it
	if(!hover)
	{
		//if texture is defined
		if(texture)
			graphics.drawImage(x, y, w, h, texture, false);
		else
		{
			graphics.drawRect(x, y, x + w, y + h);
		}
	}
	else
	{
		//if hovertexture is defined
		if (hoverTexture)
			graphics.drawImage(x, y, w, h, hoverTexture, false);
		else
		{
			graphics.fillRect(x, y, x + w, y + h);
		}
	}
}

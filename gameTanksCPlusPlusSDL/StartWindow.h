#pragma once

#include "Menu.h"

class StartWindow : public Menu
{
private:
	std::string text = "мюфлхре дкъ опнднкфемхъ";

public:
	
	StartWindow(std::vector<SDL_Surface*>&V, TTF_Font* f) {
		this->font = f;
		this->btBg = V[menuObjects::BUTTON_BG];
		this->winBg = V[menuObjects::WIN_BG];
		
	}

	virtual void blit(SDL_Surface* surface) override {
		SDL_BlitScaled(winBg, NULL, surface, &menuRect);
		blitTxtRect(surface, text, { config::winWidth / 2, config::winHeight/2, 400, 50 });
	}

	~StartWindow()
	{

	}
};


#pragma once

#include "Menu.h"

class StartWindow : public Menu
{
private:
	std::string text = "Õ¿∆Ã»“≈ ƒÀﬂ œ–ŒƒŒÀ∆≈Õ»ﬂ";

public:
	
	StartWindow(std::vector<SDL_Surface*>V, TTF_Font* f) {
		this->font = f;
		this->btBg = V[menuObjects::BUTTON_BG];
		this->winBg = V[menuObjects::WIN_BG];
		this->btns = {
			{"»√–¿“‹", {config::winWidth / 2, 80, 150, 60}},
		};
	}

	~StartWindow()
	{

	}

	virtual void blit(SDL_Surface* surface) final {

		SDL_BlitScaled(winBg, NULL, surface, &menuRect);
		blitTxtRect(surface, text, { config::winWidth / 2, config::winHeight / 2, 400, 50 });

		blitBtn(surface);
	}

};


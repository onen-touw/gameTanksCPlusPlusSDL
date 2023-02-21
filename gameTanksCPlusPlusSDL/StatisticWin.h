#pragma once

#include"Menu.h"

class StatisticWin : public Menu
{
private:
	std::string statText = "";

public:

	StatisticWin(std::vector<SDL_Surface*>& V, TTF_Font* f) {
		this->font = f;
		this->btBg = V[menuObjects::BUTTON_BG];
		this->winBg = V[menuObjects::WIN_BG];
		this->btns = {
			{"Õ¿«¿ƒ", {config::winWidth - 250, config::winHeight - 100, 200, 60}},
		};
		this->text = "—“¿“»“—» ¿";
	}
	~StatisticWin()
	{

	}

	virtual void blit(SDL_Surface* surface) override {
		SDL_BlitScaled(winBg, NULL, surface, &menuRect);
		blitTxtRect(surface, text, { config::winWidth / 2, 50, 400, 50 });
		//blitTxtRect(surface, textAbout, { config::winWidth / 2, 100, 400, 50 });


		blitBtn(surface);
	}


};


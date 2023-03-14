#pragma once
#include "Menu.h"
class ResultWin :
    public Menu
{
public:
	ResultWin(std::vector<SDL_Surface*>& V, TTF_Font* f, bool res) {
		this->font = f;
		this->btBg = V[menuObjects::BUTTON_BG];
		this->winBg = V[menuObjects::WIN_BG];
		this->menuRect = { (config::winWidth - config::rightBlockW)/2 - 300,  config::winHeight/2 - 150 ,600, 300};
		this->btns = {
			{res ? "Вы выйграли!" : "Вы проиграли!", menuRect},
		};
		winId = ResultGameWin;
	}
	~ResultWin() {}


	virtual void blit(SDL_Surface* surface) override {
		SDL_BlitScaled(winBg, NULL, surface, &menuRect);
		//blitTxtRect(surface, text, menuRect);

		blitBtn(surface);
	}

};


#pragma once

#include "Menu.h"

class menuMainWin : public Menu
{
private:

public:
	menuMainWin(std::vector<SDL_Surface*>& V, TTF_Font* f) {
	this->font = f;
	this->btBg = V[menuObjects::BUTTON_BG];
	this->winBg = V[menuObjects::WIN_BG];
	this->btns = {
		{"»√–¿“‹", {config::winWidth / 2, 120, 200, 60}},
		{"—“¿“»—“» ¿", {config::winWidth / 2, 190, 200, 60}},
		{"Œ¡ »√–≈", {config::winWidth / 2, 260, 200, 60}},
		{"¬€’Œƒ", {config::winWidth / 2, 330, 200, 60}},
	};
	text = "√À¿¬ÕŒ≈ Ã≈Õﬁ";
}
	~menuMainWin()
	{

	}

	void btnHandler() override {

	}



	virtual void blit(SDL_Surface* surface) override {
		SDL_BlitScaled(winBg, NULL, surface, &menuRect);
		blitTxtRect(surface, text, { config::winWidth / 2, 50, 400, 50 });

		blitBtn(surface);
	}

};

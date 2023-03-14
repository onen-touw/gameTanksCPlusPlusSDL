#pragma once

#include "Menu.h"

class menuMainWin : public Menu
{
public:
	enum btnId : uint8_t
	{
		PLAY,
		//STATISTIC,
		ABOUT,
		CANCEL,
		QUIT
	};

public:
	menuMainWin(std::vector<SDL_Surface*>& V, TTF_Font* f) {
		this->font = f;
		this->btBg = V[menuObjects::BUTTON_BG];
		this->winBg = V[menuObjects::WIN_BG];
		this->btns = {
			{"»√–¿“‹", {config::winWidth / 2 - 100, 120, 200, 60}, PLAY},
			//{"—“¿“»—“» ¿", {config::winWidth / 2 - 100, 190, 200, 60}, STATISTIC},
			{"Œ¡ »√–≈", {config::winWidth / 2 - 100, 190, 200, 60}, ABOUT},
			{"Œ“Ã≈Õ¿", {config::winWidth / 2 - 100, 260, 200, 60}, CANCEL},
			{"¬€’Œƒ", {config::winWidth / 2 - 100, 330, 200, 60}, QUIT},
		};
		winId = MainWin;
		text = "√À¿¬ÕŒ≈ Ã≈Õﬁ";
	}
	~menuMainWin(){}

	/*void btnHandler() override {

	}*/
	
	virtual void blit(SDL_Surface* surface) override {
		SDL_BlitScaled(winBg, NULL, surface, &menuRect);
		blitTxtRect(surface, text, { config::winWidth / 2, 50, 400, 50 });

		blitBtn(surface);
	}

};

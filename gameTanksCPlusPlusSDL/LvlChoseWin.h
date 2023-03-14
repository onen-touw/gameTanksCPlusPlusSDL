#pragma once
#include "Menu.h"
class LvlChoseWin :
    public Menu
{

public:
	enum btnId : uint8_t
	{
		LVL1,
		LVL2,
		LVL3,
		CANCEL,
	};

public:
	LvlChoseWin(std::vector<SDL_Surface*>& V, TTF_Font* f) {
		this->font = f;
		this->btBg = V[menuObjects::BUTTON_BG];
		this->winBg = V[menuObjects::WIN_BG];
		this->btns = {
			{"LVL1", {config::winWidth / 2 - 100, 120, 200, 60}, LVL1},
			{"LVL2", {config::winWidth / 2 - 100, 190, 200, 60}, LVL2},
			{"LVL3", {config::winWidth / 2 - 100, 260, 200, 60}, LVL3},
			{"Œ“Ã≈Õ¿", {config::winWidth / 2 - 100, 330, 200, 60}, CANCEL},
		};
		winId = lvlChoseWin;
		text = "√À¿¬ÕŒ≈ Ã≈Õﬁ";
	}
	~LvlChoseWin() {}


	virtual void blit(SDL_Surface* surface) final {
		SDL_BlitScaled(winBg, NULL, surface, &menuRect);
		blitTxtRect(surface, text, { config::winWidth / 2, 50, 400, 50 });

		blitBtn(surface);
	}

};


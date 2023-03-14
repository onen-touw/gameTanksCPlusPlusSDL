#pragma once
#include "Menu.h"
class RightPanel :
    public Menu
{
private:
	uint8_t tanksCount = 0;
public:
	RightPanel(std::vector<SDL_Surface*>& V, TTF_Font* f, uint8_t tanksCount) {
		this->font = f;
		this->btBg = V[menuObjects::BUTTON_BG];
		this->winBg = V[menuObjects::WIN_BG];
		this->menuRect = { config::winWidth - config::rightBlockW,  0 ,config::rightBlockW, config::winHeight };
		this->btns = {
			{"Ã≈Õﬁ", {config::winWidth - config::rightBlockW +25, 20, 150, 60}},
		};
		this->tanksCount = tanksCount;
	}
	~RightPanel() {}

	void setText(uint8_t currentKillsCount = 0) {
		text = "”·ËÚÓ " + std::to_string(currentKillsCount) + "/" + std::to_string(tanksCount);
	}

	virtual void blit(SDL_Surface* surface) final {
		SDL_BlitScaled(winBg, NULL, surface, &menuRect);
		blitTxtRect(surface, text, { config::winWidth-100,  200 ,config::rightBlockW, 100 });

		blitBtn(surface);
	}

};


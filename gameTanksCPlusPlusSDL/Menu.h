#pragma once


#include"Object.h"


class Menu :public Object
{

public:
	enum menuId :uint8_t
	{
		unknown,
		MainWin,
		StatWin,
		AbtWin,
		lvlChoseWin,
		ResultGameWin
	};


protected:
	std::vector<btnsStruct> btns = {};
	SDL_Surface* winBg = nullptr;
	SDL_Surface* btBg = nullptr;
	TTF_Font* font = nullptr;

	std::string text = "";

	SDL_Color color = { 0, 0, 0 };

	SDL_Rect menuRect = { 0, 0, config::winWidth, config::winHeight };

	menuId winId = unknown;


public:
	Menu(){
		
	}

	~Menu() override {
	#ifdef DEBUG
		std::cout << "MENU::deconstructor\n";
	#endif // DEBUG
	}

	int8_t checkButtonClick(int x, int y) {
		if (!this->btns.empty())
		{
			for (size_t i = 0; i < this->btns.size(); ++i)
			{
				if (btns[i].click(x,y))
				{
					return btns[i].id;
				}
			}
		}
		return -1;
	}

	menuId getWinId() const { return winId; }


	void blitBtn(SDL_Surface* surface) {
		if (!btns.empty())
		{
			btnsStruct tmp = {};
			for (auto& el : btns)
			{
				tmp = el;
				tmp.rect.x = tmp.rect.x + tmp.rect.w / 2;	
				tmp.rect.y = tmp.rect.y + tmp.rect.h / 2;
				SDL_BlitScaled(btBg, NULL, surface, &el.rect);
				blitTxtRect(surface, el.text, tmp.rect);
			}
		}
	}

	void blitTxtRect(SDL_Surface* surface, std::string txt, SDL_Rect rect) {
		if (txt.empty()) return;
		
		rect.x = rect.x - rect.w/2;
		rect.y = rect.y - rect.h/2;
		SDL_Surface* tempSurf = TTF_RenderText_Solid(this->font, txt.c_str(), color);
		rect = { rect.x + (rect.w - tempSurf->w) / 2, rect.y +
			(rect.h - tempSurf->h) / 2,0,0 };
		SDL_BlitSurface(tempSurf, NULL, surface, &rect);
		SDL_FreeSurface(tempSurf);
	}

	virtual void blit(SDL_Surface*) = 0;

};
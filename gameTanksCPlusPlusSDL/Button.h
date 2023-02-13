#include "globals.h"

class Button
{
private:
	SDL_Surface* btBg = nullptr;
	TTF_Font* font = nullptr;
	std::vector<btnsStruct> btns = {};
	SDL_Color color = { 255, 255, 255 };
public:
	Button(SDL_Surface* btBg, TTF_Font* font, std::vector<btnsStruct> btns): 
		btBg(btBg), font(font), btns(btns){}
	~Button(){}

	void blitBtn(SDL_Surface* surface) {
		btnsStruct tmp = {};
		for (size_t i = 0; i < btns.size(); ++i)
		{
			 tmp = btns[i];

			SDL_BlitScaled(btBg, NULL, surface, &tmp.rect);
			SDL_Surface* tempSurf = TTF_RenderText_Solid(this->font, tmp.text.c_str(), color);
			SDL_Rect tempRect = { tmp.rect.x + (tmp.rect.w - tempSurf->w) / 2, tmp.rect.y + 
				(tmp.rect.h - tempSurf->h) / 2,0,0 };
			SDL_BlitSurface(tempSurf, NULL, surface, &tempRect);
			SDL_FreeSurface(tempSurf);
		}
	}

	int8_t checkButtonClick(int x, int y) {
		if (!this->btns.empty())
		{
			for (size_t i = 0; i < this->btns.size(); ++i)
			{
				if (x >= this->btns[i].rect.x && x <= this->btns[i].rect.x + this->btns[i].rect.w
					&& y >= this->btns[i].rect.y && y <= this->btns[i].rect.y + this->btns[i].rect.h)
				{
					return i;
				}
			}
		}
		return -1;
	}

};

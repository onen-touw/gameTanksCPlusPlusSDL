#include"Object.h"


class Menu:public Object
{

protected:
	std::vector<btnsStruct> btns = {};
	SDL_Surface* winBg = nullptr;
	SDL_Surface* btBg = nullptr;
	TTF_Font* font = nullptr;

	SDL_Color color = { 0, 0, 0 };

	SDL_Rect menuRect = { 0, 0, config::winWidth, config::winHeight };

public:
	Menu(){
		
	}

	~Menu() override {
	#ifdef DEBUG
		std::cout << "MENU::deconstructor\n";
	#endif // DEBUG
	}


	void blitBtn(SDL_Surface* surface) {
		if (!btns.empty())
		{
			btnsStruct tmp = {};
			for (auto& el : btns)
			{
				tmp = el;
				tmp.rect.x = tmp.rect.x - tmp.rect.w / 2;
				tmp.rect.y = tmp.rect.y - tmp.rect.h / 2;
				SDL_BlitScaled(btBg, NULL, surface, &tmp.rect);
				blitTxtRect(surface, el.text, el.rect);
			}
		}
	}

	
	void blitTxtRect(SDL_Surface* surface, std::string txt, SDL_Rect rect) {
		rect.x = rect.x - rect.w/2;
		rect.y = rect.y - rect.h/2;
		SDL_Surface* tempSurf = TTF_RenderText_Solid(this->font, txt.c_str(), color);
		rect = { rect.x + (rect.w - tempSurf->w) / 2, rect.y +
			(rect.h - tempSurf->h) / 2,0,0 };
		SDL_BlitSurface(tempSurf, NULL, surface, &rect);
		SDL_FreeSurface(tempSurf);
	}

	//void blitBtns() {
	//	
	//}

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

	virtual void blit(SDL_Surface*) override {}

};


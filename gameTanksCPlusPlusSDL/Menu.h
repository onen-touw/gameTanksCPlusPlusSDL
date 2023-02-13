#include"Object.h"
#include"Button.h"

class Menu:public Object, private Button
{
public:
	Menu(SDL_Surface* btBg, TTF_Font* font, std::vector<btnsStruct> btns) : Button(btBg, font, btns) {
	}
	~Menu() {}

private:

	virtual void blit(SDL_Surface*) override {

	}

};


#pragma once

#include"Menu.h"
#include"aboutWin.h"
#include"menuMainWin.h"
#include"StatisticWin.h"
//#include"testClass.h"

class MenuHandler
{
private:

	Menu* win = nullptr;
	bool winState = false;

public:
	MenuHandler() {

	}
	~MenuHandler()
	{

	}

	void menuOpen() {
		winState = true;
		//win = new menuMainWin();
	}

	void handler(SDL_Event& event) {
		int x = 0, y = 0;
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_GetMouseState(&x, &y);
			//win->(x, y);
		}

	}


};


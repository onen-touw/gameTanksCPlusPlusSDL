#pragma once

#include"aboutWin.h"
#include"menuMainWin.h"
#include"StatisticWin.h"
#include"StartWindow.h"
#include"LvlChoseWin.h"
#include"ResultWin.h"

class MenuHandler
{  
private:

	std::vector<Menu*> menuWindows;
	TTF_Font* font = nullptr;
	std::vector<SDL_Surface*> menuImages;
	bool btnCancelLock = true;

public:
	MenuHandler(std::vector<SDL_Surface*>& menuImages, TTF_Font* font) : menuImages(menuImages), font(font){}
	~MenuHandler()
	{
		menuWindows.push_back(new menuMainWin(menuImages, font));
	}

	void clearMenuQueue() { menuWindows.clear(); }

	void startingWin() { menuWindows.push_back(new StartWindow(menuImages, font)); }

	void openResultWin(bool res){ menuWindows.push_back(new ResultWin(menuImages, font, res)); }

	void openMenu(bool cancelBtnFlag = false) { 
		btnCancelLock = cancelBtnFlag;
		menuWindows.clear(); 
		menuWindows.push_back(new menuMainWin(menuImages, font)); 
	}

	bool isMenu() const { return menuWindows.empty(); }
	
	void handler(SDL_Event& event, gameStates& gs, std::function<void(std::string)>BuildGame) {
		if (isMenu()) return;
		int x = 0, y = 0;
		
		if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP)
		{
			SDL_GetMouseState(&x, &y);
			switch (menuWindows.back()->getWinId())
			{
			case Menu::menuId::MainWin:
				switch (menuWindows.back()->checkButtonClick(x, y))
				{
				case menuMainWin::btnId::PLAY:
					menuWindows.push_back(new LvlChoseWin(menuImages, font));
					break;
				case menuMainWin::btnId::ABOUT:
					menuWindows.push_back(new aboutWin(menuImages, font));
					break;
				/*case menuMainWin::btnId::STATISTIC:
					menuWindows.push_back(new StatisticWin(menuImages, font));
					std::cout << "STATISTIC\n";
					break;*/
				case menuMainWin::btnId::CANCEL:
					if (!btnCancelLock)
					{
						menuWindows.clear();
						gs = Playing;
					}
					break;
				case menuMainWin::btnId::QUIT:
					gs = Quit;
					menuWindows.clear();
					break;
				default:
					break;
				}  
				break; 
			case Menu::menuId::AbtWin:
				if (menuWindows.back()->checkButtonClick(x,y) == 0) menuWindows.pop_back();
				break;
			case Menu::menuId::StatWin:
				if (menuWindows.back()->checkButtonClick(x, y) == 0) menuWindows.pop_back();
				break;

			case Menu::menuId::lvlChoseWin:
				switch (menuWindows.back()->checkButtonClick(x, y))
				{
				case LvlChoseWin::btnId::LVL1:
					std::cout << "LVL1\n";
					BuildGame("lvl1.txt");
					gs = Playing;
					break;
				case LvlChoseWin::btnId::LVL2:
					std::cout << "LVL2\n";
					BuildGame("lvl2.txt");
					gs = Playing;
					break;
				case LvlChoseWin::btnId::LVL3:
					std::cout << "LVL3\n";
					BuildGame("lvl3.txt");
					gs = Playing;
					break;
				case LvlChoseWin::btnId::CANCEL:
					menuWindows.pop_back();
					return;
					break;

				default:
					break;
				}
				break;
			case Menu::menuId::ResultGameWin:
				if (menuWindows.back()->checkButtonClick(x, y) == 0) 
				{
					menuWindows.pop_back();
					openMenu(true);
					gs = MenuHandling;
				}
				break;

			default:
				break;
			}
		}
		

	}
	void blit(SDL_Surface* surface){
		if (!menuWindows.empty()) menuWindows.back()->blit(surface);
	}


};


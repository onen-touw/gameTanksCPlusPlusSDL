#pragma once

#include"globals.h"

class baseGameClass
{
protected:
	SDL_Window* win = nullptr;
	SDL_Surface* surface = nullptr;
public:

	baseGameClass(){}
	~baseGameClass(){
#ifdef DEBUG
		std::cout << "baseGameClass::deconstructor\n";
#endif // DEBUG
		SDL_FreeSurface(surface);
		SDL_DestroyWindow(win);

		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
	}


	bool initModuls() {
		bool success = true;

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			success = false;
		}
		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags)) {
			std::cout << "Can't init image: " << IMG_GetError() << std::endl;
			success = false;
		}
		
		win = SDL_CreateWindow(config::winTitle, 100, 100,
			config::winWidth, config::winHeight, SDL_WINDOW_SHOWN);
		
		if (win == NULL) {
			std::cout << "Can't create window: " << SDL_GetError() << std::endl;
			success = false;
		}
		surface = SDL_GetWindowSurface(win);

		if (TTF_Init() != 0)
		{
			std::cout << "problem::ttfInit\n";
			success = false;
		}

		return success;
	}

	//void rebuildWin() {//+

	//	SDL_FreeSurface(Surface);
	//	SDL_DestroyWindow(settingGGame::win);

	//	switch (settingGGame::hardnes)
	//	{
	//	case hardnesSettingsEnum::easy:
	//		settingGGame::gSizes.winWIDTH = settingGGame::hardSetting.easySizeWigth * settingGGame::gSizes.cellSize;
	//		settingGGame::gSizes.winHEIGHT = settingGGame::hardSetting.easySizeHeight * settingGGame::gSizes.cellSize;
	//		break;
	//	case hardnesSettingsEnum::normal:
	//		settingGGame::gSizes.winWIDTH = settingGGame::hardSetting.normalSizeWidth * settingGGame::gSizes.cellSize;
	//		settingGGame::gSizes.winHEIGHT = settingGGame::hardSetting.normalSizeHeight * settingGGame::gSizes.cellSize;
	//		break;
	//	case hardnesSettingsEnum::hard:
	//		settingGGame::gSizes.winWIDTH = settingGGame::hardSetting.hardSizeWidth * settingGGame::gSizes.cellSize;
	//		settingGGame::gSizes.winHEIGHT = settingGGame::hardSetting.hardSizeHeight * settingGGame::gSizes.cellSize;
	//		break;

	//	default:
	//		break;
	//	}
	//	settingGGame::gSizes.winHEIGHT +=settingGGame::gSizes.menuHeaderHeight;
	//	std::cout << settingGGame::gSizes.winWIDTH << "x" << settingGGame::gSizes.winHEIGHT << "\n";
	//	settingGGame::win = SDL_CreateWindow("DeminerGame", 100, 100,
	//		settingGGame::gSizes.winWIDTH, settingGGame::gSizes.winHEIGHT,
	//		SDL_WINDOW_SHOWN);
	//	settingGGame::Surface = SDL_GetWindowSurface(settingGGame::win);
	//}

};


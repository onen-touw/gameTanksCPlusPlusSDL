#pragma once

#include "globals.h"

class baseGameClass 
{
protected:
	SDL_Window* win = nullptr;
	SDL_Surface* surface = nullptr;

	enum gameSceneObjects : uint8_t
	{
		FIELD,
		CHARACTER_TANK,
		BOT_TANK_TT,
		BOT_TANK_LT,
		BULLETS,
	};

private:
	
	/// to array matrix[][]
	 std::vector<imagePath>fieldImagesPathVector = {
		{"./image/field/emptyCell.png", cellObjects::Empty},
		{"./image/field/wall.png", cellObjects::Wall},
		{"./image/field/hardWall.png", cellObjects::HardWall},
	};
	
	 std::vector<imagePath>bulletImagesPathVector = {			
		{"./image/tank/bullets/up.png", direction::UP},
		{"./image/tank/bullets/right.png", direction::RIGHT},
		{"./image/tank/bullets/down.png", direction::DOWN},
		{"./image/tank/bullets/left.png", direction::LEFT},
	};


	 std::vector<imagePath>TankTTImagesPathVector = {
		{"./image/tank/botTT/up.png", direction::UP},
		{"./image/tank/botTT/right.png", direction::RIGHT},
		{"./image/tank/botTT/down.png", direction::DOWN},
		{"./image/tank/botTT/left.png", direction::LEFT},
	};

	 std::vector<imagePath>TankCharacterImagesPathVector = {
		{"./image/tank/character/up.png", direction::UP},
		{"./image/tank/character/down.png", direction::DOWN},
		{"./image/tank/character/right.png", direction::RIGHT},
		{"./image/tank/character/left.png", direction::LEFT},
	};
protected:
	std::vector<SDL_Surface*>fieldImages = {};
	std::vector<SDL_Surface*>bulletImages = {};
	std::vector<SDL_Surface*>tankTTImages = {};
	std::vector<SDL_Surface*>TankCharacterImages = {};


private: 
	void loadImages(std::vector<imagePath>&vPaths, std::vector<SDL_Surface*>&vSurf)
	{
		vSurf.resize(vPaths.size());

		imagePath tmp = {};

		for (int i = 0; i < vPaths.size(); i++)
		{
			tmp = vPaths[i];
			vSurf[tmp.id] = IMG_Load(tmp.path.c_str());

			if (vSurf[tmp.id] == nullptr)
			{
	#ifdef DEBUG
				std::cout << "Can't load: " << IMG_GetError() << std::endl;
	#endif // DEBUG
			}
			else
			{
	#ifdef DEBUG
				std::cout << "picture uploaded:: #" << static_cast<uint16_t>(vPaths[i].id) << "\n";
	#endif // DEBUG
			}
		}
		return;
	}

public:

	baseGameClass(){}
	~baseGameClass(){
		SDL_FreeSurface(surface);
		SDL_DestroyWindow(win);

		IMG_Quit();
		TTF_Quit();
		SDL_Quit();

	#ifdef DEBUG
		std::cout << "baseGameClass::deconstructor\n";
	#endif // DEBUG
	}

	void initModuls() {

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			errors::errorStatus = ErrorsCodes::SDL_INIT_ERROR;
		}
		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags)) {
			//std::cout << "Can't init image: " << IMG_GetError() << std::endl;
			errors::errorStatus = ErrorsCodes::SDL_IMAGE_INIT_ERROR;
		}

		if (TTF_Init() != 0)
		{
			errors::errorStatus = ErrorsCodes::SDL_TTF_INIT_ERROR;
			//std::cout << "problem::ttfInit\n";
		}
		
		win = SDL_CreateWindow(config::winTitle, 100, 100,
			config::winWidth, config::winHeight, SDL_WINDOW_SHOWN);
		if (win == NULL) {
			errors::errorStatus = ErrorsCodes::SDL_WIN_CREATE_ERROR;
			//std::cout << "Can't create window: " << SDL_GetError() << std::endl;
		}

		surface = SDL_GetWindowSurface(win);
		if (surface == nullptr)
		{
			errors::errorStatus = ErrorsCodes::SDL_TARGET_SURFACE_CREATE_ERROR;
		}
		return;
	}
	
	void loadResourses() {

		loadImages(fieldImagesPathVector, fieldImages);
		loadImages(bulletImagesPathVector, bulletImages);
		loadImages(TankTTImagesPathVector, tankTTImages);
		loadImages(TankCharacterImagesPathVector, TankCharacterImages);
	}


};


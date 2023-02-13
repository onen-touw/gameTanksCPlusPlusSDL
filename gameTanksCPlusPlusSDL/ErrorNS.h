#pragma once

#include<iostream>

enum ErrorsCodes : uint8_t
{
	OK, 
	IMG_LOADING_ERROR = 100, 
	IMG_GETTING_ERROR,
	MAP_LOADING_ERROR,
	FONT_OPEN_ERROR,
	SDL_INIT_ERROR = 200,
	SDL_IMAGE_INIT_ERROR,
	SDL_TTF_INIT_ERROR,
	SDL_WIN_CREATE_ERROR,
	SDL_TARGET_SURFACE_CREATE_ERROR,
};

namespace errors {
	extern uint8_t errorStatus;
}


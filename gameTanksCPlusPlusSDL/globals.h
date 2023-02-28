#pragma once

#ifndef DEBUG
///for consol debug
#define DEBUG
#endif // !DEBUG

#include "ErrorNS.h"
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<vector>
#include<string>

enum direction : uint8_t
{
	UP,
	LEFT,
	DOWN,
	RIGHT
};

enum cellObjects: uint8_t
{
	Empty, Wall, HardWall,
};

enum menuObjects : uint8_t
{
	BUTTON_BG, WIN_BG,
};

struct cell
{
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t objHp = 0;
	uint8_t obj = cellObjects::Empty;
};

struct bulletStruct
{
	uint16_t x = 0;
	uint16_t y = 0;
	direction direct;
};

struct imagePath
{
	std::string path;
	uint8_t id;
};

struct point
{
	uint32_t i = 0, j = 0;
};

struct btnsStruct
{
	std::string text = "";
	SDL_Rect rect = { 0,0,200, 60 };		/// default sizes for btns
};


class config
{
public:

	static constexpr uint8_t cellSize = 30;											///px
	static constexpr uint8_t cellsWCount = 40;										///cells
	static constexpr uint8_t cellsHCount = 25;										///cells
	static constexpr uint8_t rightBlockW = 200;										///px

	static constexpr uint16_t winHeight = cellsHCount * cellSize;					///px
	static constexpr uint16_t winWidth = cellsWCount * cellSize + rightBlockW;		///px

	static constexpr uint8_t tankSpeed = 10;										///px
	static constexpr uint8_t bulletSpeed = 30;										///px

	static constexpr uint8_t FPS = 60;												///px
	
	static constexpr const char* winTitle = "TanksGame";							///windowName

};

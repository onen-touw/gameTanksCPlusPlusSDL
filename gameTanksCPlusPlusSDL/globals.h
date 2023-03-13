#pragma once

///for consol debuging
#define DEBUG

#include<iostream>
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
	Empty, Wall, Wall66Perc, Wall33Perc, HardWall,
};

enum _objHP : uint8_t
{
	Full=2, Broken66=1, Broken33=0
};

enum menuObjects : uint8_t
{
	BUTTON_BG, WIN_BG,
};

struct cell
{
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t objHp = _objHP::Full;
	cellObjects obj = cellObjects::Empty;

	void breakWall() {
		if (this->objHp > 0)
		{
			--objHp;
		}
		else
		{
			this->obj = cellObjects::Empty;
		}
	}

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
	int32_t i = 0, j = 0;
	bool operator == (const point& other) { return (i == other.i && j == other.j); }
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

	static constexpr uint8_t bulletSpeed = 20;										///px

	static constexpr uint32_t moveTanksDelay = 400;									///milliseconds

	static constexpr uint8_t bulletMaxFlyDistance = 10;								///cells

	///if distance on the waveMap is less than this param than 
	///bot starts moving to the target
	static constexpr uint8_t detectionByLenthOfWay = 25;							///cells on waveMap

	///if distance on the waveMap is greater than this param than 
	///bot can move to the target
	static constexpr uint8_t minimalTargetDistanse = 1;								///cells on waveMap

	static constexpr uint8_t FPS = 60;												///px
	
	static constexpr const char* winTitle = "TanksGame";							///windowName

};

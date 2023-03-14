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

enum gameStates : uint8_t
{
	HelloWin,
	MenuHandling,
	Playing,
	GameResalt,
	Quit
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
	uint8_t id = 0;
	bool click(int32_t mouseX, int32_t mouseY) {
		return (mouseX >= rect.x && mouseX <= rect.x + rect.w
			&& mouseY >= rect.y && mouseY <= rect.y + rect.h);
	}
};


class config
{
public:

	static constexpr uint8_t cellSize = 30u;											///px
	static constexpr uint8_t cellsWCount = 40u;											///cells
	static constexpr uint8_t cellsHCount = 25u;											///cells
	static constexpr uint8_t rightBlockW = 200u;										///px

	static constexpr uint16_t winHeight = cellsHCount * cellSize;						///px
	static constexpr uint16_t winWidth = cellsWCount * cellSize + rightBlockW;			///px

	static constexpr uint8_t bulletSpeed = 20u;											///px

	static constexpr uint32_t moveTanksDelay = 400u;									///milliseconds

	static constexpr uint8_t bulletMaxFlyDistance = 10u;								///cells

	///if distance on the waveMap is less than this param than 
	///bot starts moving to the target
	static constexpr uint8_t detectionByLenthOfWay = 25u;								///cells on waveMap

	///if distance on the waveMap is greater than this param than 
	///bot can move to the target
	static constexpr uint8_t minimalTargetDistanse = 0u;								///cells on waveMap

	static constexpr uint8_t FPS = 60u;													///px
	
	static constexpr const char* winTitle = "TanksGame";								///windowName

};

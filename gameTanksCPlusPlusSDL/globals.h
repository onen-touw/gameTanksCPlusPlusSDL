#pragma once

#ifndef DEBUG
///for consol debug
#define DEBUG
#endif // !DEBUG



#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<vector>
#include<string>

enum cellObjects: uint8_t
{
	Empty, Wall, HardWall,
};

struct cell
{
	uint8_t x = 0;
	uint8_t y = 0;
	uint8_t objHp = 0;
	uint8_t obj = cellObjects::Empty;
};

struct imagePath
{
	std::string path;
	short int id;
};

struct point
{
	uint8_t p1 = 0;
	uint8_t p2 = 0;
};

enum direction
{
	up,
	right,
	left,
	down,

	nomberOfDirections
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

	/*static constexpr const char* imgPath = "./";
	static constexpr const char* fontPath = "./";*/

	static constexpr const char* winTitle = "TanksGame";

	std::vector<imagePath>fieldImagesPathVector = {
		{"./image/field/emptyCell.png", cellObjects::Empty},
		{"./image/field/wall.png", cellObjects::Wall},
		{"./image/field/hardWall.png", cellObjects::HardWall},
	};

	config() {}
	~config(){}

};

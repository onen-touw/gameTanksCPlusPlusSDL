#pragma once

#include"Object.h"
#include"loadingFieldResourses.h"


class Field : public Object, private loadingFieldResourses
{
private:
	std::vector<std::vector<cell>>field;
	std::vector<imagePath>fieldImagesPathVector = {
		{"./image/field/emptyCell.png", cellObjects::Empty},
		{"./image/field/wall.png", cellObjects::Wall},
		{"./image/field/hardWall.png", cellObjects::HardWall},
	};


private:
	void fDebug() {
		for (size_t i = 0; i < field.size(); ++i)
		{
			for (size_t j = 0; j < field[i].size(); ++j)
			{
				std::cout << static_cast<uint16_t> (field[i][j].obj) << " ";
				/*std::cout << "(" << static_cast<uint16_t>(field[i][j].x)
					<< " " << static_cast<uint16_t>(field[i][j].y) << ") ";*/
			}
			std::cout << "\n";
		}
	}

public:

	std::vector<std::vector<cell>>getField() {
		return this->field;
	}


	Field(std::string mapName) {
		field.resize(config::cellsHCount);
		for (size_t i = 0; i < field.size(); ++i)
		{
			field[i].resize(config::cellsWCount);
		}
		int x = 0, y = 0;
		for (size_t i = 0; i < field.size(); ++i)
		{
			for (size_t j = 0; j < field[i].size(); ++j)
			{
				field[i][j].x = x;
				field[i][j].y = y;
				x += this->cellPxSize;
			}
			y += this->cellPxSize;
			x = 0;
		}
		this->openMap(mapName, field);
		this->loadImages(this->fieldImagesPathVector);

#ifdef DEBUG
		std::cout << "Field::constructor\n";
		this->fDebug();
		this->logOut();
#endif // DEBUG
	}


	~Field() {
#ifdef DEBUG
		std::cout << "Field::deconstructor\n";
#endif // DEBUG
	}


public:
	virtual void blit(SDL_Surface* surface) final {
		SDL_Rect rc = {};
		cell tmp = {};

		for (size_t i = 0; i < field.size(); ++i)
		{
			for (size_t j = 0; j < field[i].size(); ++j)
			{
				tmp = field[i][j];
				rc = { tmp.x, tmp.y, this->cellPxSize,this->cellPxSize };

				switch (tmp.obj)
				{
				case cellObjects::Empty:
					SDL_BlitScaled(this->images[cellObjects::Empty], NULL, surface, &rc);
					break;
				case cellObjects::Wall:
					SDL_BlitScaled(this->images[cellObjects::Wall], NULL, surface, &rc);
					break;
				case cellObjects::HardWall:
					SDL_BlitScaled(this->images[cellObjects::HardWall], NULL, surface, &rc);
					break;
				default:
					break;
				}
			}
		}
	}
};


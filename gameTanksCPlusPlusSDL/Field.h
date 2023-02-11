#pragma once

#include"Object.h"
#include"loadingFieldResourses.h"


class Field : public Object, private loadingFieldResourses
{
private:
	std::vector<std::vector<cell>>field;

private:
	std::vector<std::vector<cell>>& getFieldLink() { return field; }

	void fDebug() {
		for (size_t i = 0; i < field.size(); ++i)
		{
			for (size_t j = 0; j < field[i].size(); ++j)
			{
				std::cout << static_cast<uint16_t> (field[i][j].obj) << " ";
			}
			std::cout << "\n";
		}
	}

public:
	Field() {

#ifdef DEBUG
		std::cout << "Field::constructor\n";
		
#endif // DEBUG

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
		this->openMap("lvl1.txt", this->getFieldLink());

#ifdef DEBUG
		this->fDebug();
#endif // DEBUG
	}


	~Field() {
#ifdef DEBUG
		std::cout << "Field::deconstructor\n";
#endif // DEBUG
	}

protected:
	void blitCell(int x, int y, SDL_Surface* img) {
		SDL_Rect rc = { x, y, this->cellPxSize,this->cellPxSize, };
		//SDL_BlitScaled(img, NULL, Surface, &rc);
	}

public:
	virtual void blit() {
		for (size_t i = 0; i < field.size(); ++i)
		{
			for (size_t j = 0; j < field[i].size(); ++j)
			{
				cell tmp = field[i][j];
				//this->blitCell(tmp.x, tmp.y, /*img[]*/);
			}
		}
	}
};


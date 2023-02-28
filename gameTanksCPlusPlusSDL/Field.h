#pragma once

#include"Object.h"
#include<fstream>


class Field : public Object
{
private:
	std::vector<std::vector<cell>>field;
	std::vector<SDL_Surface*>images;
	std::string saveFolder = "save/";


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

	///example path: lvl1.txt
	void openMap(std::string path, std::vector<std::vector<cell>>& V) {

		std::ifstream file((this->saveFolder + path).c_str());
		if (file.is_open())
		{
	#ifdef DEBUG
			std::cout << "file::open\n";
	#endif // DEBUG
			std::string tempStr = "";

			int l = 0, m = 0, k = 0;
			while (std::getline(file, tempStr))
			{
				k = 0;
				m = 0;
				while (tempStr[k] != '\0')
				{
					if (tempStr[k] == '/')
					{
						k++;
					}
					if (tempStr[k] == '\0')
					{
						break;
					}

					V[l][m].obj = static_cast<uint8_t>(tempStr[k] - '0');
					V[l][m].objHp = static_cast<uint8_t>(tempStr[++k] - '0');
					m++;
					k++;
				}
				l++;

			}
			tempStr.clear();
			file.close();
		}
		else
		{
			errors::errorStatus = ErrorsCodes::MAP_LOADING_ERROR;

	#ifdef DEBUG
			std::cout << "loadingFieldResourses::openMap::loadingError file was't open\n";
	#endif // DEBUG
		}

	}

public:
	std::vector<std::vector<cell>>&getField() {
		return this->field;
	}

	Field(std::string mapName, std::vector< SDL_Surface*> vImg) : images(vImg){
		field.resize(config::cellsHCount);
		for (size_t i = 0; i < field.size(); ++i)
		{
			field[i].resize(config::cellsWCount);
		}
		uint16_t x = 0, y = 0;
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
		//this->loadImages(this->fieldImagesPathVector);

#ifdef DEBUG
		std::cout << "Field::constructor\n";
		this->fDebug();
#endif // DEBUG
	}


	~Field() override {
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


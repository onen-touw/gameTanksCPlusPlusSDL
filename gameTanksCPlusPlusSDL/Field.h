#pragma once

#include"Object.h"
#include<fstream>


class Field : public Object
{
private:
	std::vector<std::vector<cell>>field;
	std::vector<SDL_Surface*>images;
	std::vector<point>tanksPosition;

	std::string mapsFolder = "maps/";
	bool loadMapStatus = true;

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

		std::ifstream file((this->mapsFolder + path).c_str());
		if (file.is_open())
		{
	#ifdef DEBUG
			std::cout << "file::open\n";
	#endif // DEBUG
			std::string tempStr = "";
			std::string tempStr2 = "";
			std::getline(file, tempStr);
			uint8_t tanksCount = static_cast<uint8_t>(atoi(tempStr.c_str()));

			tanksPosition.resize(tanksCount);

			for (uint8_t i = 0; i < tanksCount; ++i)
			{
				tempStr.clear();
				std::getline(file, tempStr);

				uint8_t k = 0 , point_ = 0;
				while (tempStr[k] != '\0')
				{
					if (tempStr[k] != '/')
					{
						tempStr2.append(1, tempStr[k]);
					}
					else
					{
						if (point_ == 0)
						{
							std::cout << tempStr2<< "\n";
							tanksPosition[i].i = (atoi(tempStr2.c_str()));
							point_ = 1;
						}
						else
						{
							std::cout << tempStr2 << "\n";
							tanksPosition[i].j = (atoi(tempStr2.c_str()));
							point_ = 0;
						}
						tempStr2.clear();
					}
					++k;
				}
			}
			std::cout << "position from save\n";
			for (auto& el : tanksPosition)
			{
				std::cout << el.i << " x " << el.j << "\n";
			}


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

					V[l][m].obj = static_cast<cellObjects>(tempStr[k] - '0');
					V[l][m].objHp = static_cast<_objHP>(tempStr[++k] - '0');
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
			loadMapStatus = false;

	#ifdef DEBUG
			std::cout << "loadingFieldResourses::openMap::loadingError file was't open\n";
	#endif // DEBUG
		}

	}

public:

	bool getMapLoadingStatus() const { return loadMapStatus; }

	std::vector<std::vector<cell>>&getField() {
		return this->field;
	}
	std::vector<point>& getUnitPosition() { return tanksPosition; }

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
					switch (tmp.objHp)
					{
					case Full:
						SDL_BlitScaled(this->images[cellObjects::Wall], NULL, surface, &rc);
						break;
					case Broken66:
						SDL_BlitScaled(this->images[cellObjects::Wall66Perc], NULL, surface, &rc);
						break;
					case Broken33:
						SDL_BlitScaled(this->images[cellObjects::Wall33Perc], NULL, surface, &rc);
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
			}
		}
	}
};


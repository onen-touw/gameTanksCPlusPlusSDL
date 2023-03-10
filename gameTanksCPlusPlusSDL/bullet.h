#pragma once

#include"globals.h"

class bullet 
{

private:
	uint8_t speed = config::bulletSpeed;
	uint8_t cellSize = config::cellSize;

	int16_t x = 0, y = 0;

	int16_t deathX = 0, deathY = 0;	///px/px 


	uint8_t bXSize = 20;			///px 
	uint8_t bYSize = 30;			///px 
	
public:
	direction dirct = direction::UP;

	bullet(direction dirct, int16_t x, int16_t y)
		: dirct(dirct){
		this->x = x + cellSize / 2;
		this->y = y + cellSize / 2;
	}

	~bullet ()
	{

	}

	point getPosition() const { return { x, y }; }
	point getPositionCell() const { return { y / cellSize, x/cellSize }; }

	void setDeathPoint(std::vector<std::vector<cell>>&V, int16_t i, int16_t j) {
		uint8_t counter = 0;
		switch (dirct)
		{
		case UP:
			for (int32_t k = i-1ll; k > 0; --k)
			{
				if (V[k][j].obj || ++counter >= config::bulletMaxFlyDistance)
				{
					deathY = V[k][j].y + bYSize/2;
					return;
				}
			}
			break;
		case LEFT:
			for (int32_t k = j - 1ll; k > 0; --k)
			{
				if (V[i][k].obj || ++counter >= config::bulletMaxFlyDistance)
				{
					deathX = V[i][k].x + bYSize/2;
					return;
				}
			}
			break;
		case DOWN:
			for (int32_t k = i+1ll; k < V.size(); ++k)
			{
				if (V[k][j].obj || ++counter >= config::bulletMaxFlyDistance)
				{
					deathY = V[k][i].y - bYSize / 2;
					return;
				}
			}
			deathY = config::winHeight;
			break;
		case RIGHT:
			for (int32_t k = j + 1ll; k < V[i].size(); ++k)
			{
				if (V[i][k].obj || ++counter >= config::bulletMaxFlyDistance)
				{
					deathX = V[i][k].x - bYSize / 2;
					return;
				}
			}
			deathX = config::winWidth - config::rightBlockW;
			break;
		default:
			break;
		}
	}

	/// return false if the bullet died
	///TODO: check for other tanks
	bool bulletTransmit(std::vector<std::vector<cell>>& field) {
		/// checkimg other tanks

		switch (dirct)
		{
		case UP:
			if (y > deathY + cellSize)
			{
				y -= speed;
			}
			else
			{
				///recovering cell possition
				field[(deathY - bYSize / 2ll) / cellSize][x / cellSize].breakWall();
				return false;
			}
			break;
		case LEFT:
			if (x > deathX + cellSize)
			{
				x -= speed;
			}
			else
			{
				field[y / cellSize][(deathX-bYSize / 2ll) / cellSize].breakWall();
				return false;
			}
			break;
		case DOWN:
			if (y < deathY)
			{
				y += speed;
			}
			else
			{
				if (deathY >= config::winHeight) return false;
				field[(deathY + bYSize / 2ll) / cellSize][x / cellSize].breakWall();
				return false;
			}
			break;
		case RIGHT:
			if (x < deathX)
			{
				x += speed;
			}
			else
			{
				if (deathX >= config::winWidth - config::rightBlockW) return false;
				field[y/cellSize][(deathX + bYSize / 2ll) / cellSize].breakWall();
				return false;
			}
			break;
		default:
			break;
		}
		return true;
	}

	 void blit(SDL_Surface* surface, SDL_Surface* image) {
		SDL_Rect rc = {};
		if (dirct == UP || dirct == DOWN)
		{
			rc = { x - bXSize / 2, y - bYSize / 2, bXSize, bYSize };
		}
		else
		{
			rc = { x - bYSize / 2, y - bXSize / 2, bYSize, bXSize };
		}
		SDL_BlitScaled(image, NULL, surface, &rc);
	}

};


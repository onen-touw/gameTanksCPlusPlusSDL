#pragma once

#include"globals.h"

class bullet 
{

private:
	uint8_t speed = config::bulletSpeed;

	int16_t x = 0, y = 0;

	uint8_t bXSize = 20;			///px 
	uint8_t bYSize = 30;			///px 
	
public:
	direction dirct = direction::UP;

	bullet(direction dirct, uint16_t x,uint16_t y)
		: dirct(dirct)/*, x(x ), y(y + bYSize/2)*/{
		this->x = x + config::cellSize/2;
		this->y = y + config::cellSize / 2;
	}

	~bullet ()
	{

	}

	/// return false if the bullet died
	///TODO: check for walls and other tanks
	bool bulletTransmit() {
		std::cout << x << " " << y << "\n";
		switch (dirct)
		{
		case UP:
			if (y > 0)
			{
				y -= speed;
			}
			else
				return false;
			break;
		case LEFT:
			if (x > 0)
			{
				x -= speed;
			}
			else
				return false;
			break;
		case DOWN:
			if (y < config::winHeight)
			{
				y += speed;
			}
			else
				return false;
			break;
		case RIGHT:
			if (x < config::winWidth - config::rightBlockW)
			{
				x += speed;
			}
			else
				return false;
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


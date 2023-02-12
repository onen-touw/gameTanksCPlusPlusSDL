#pragma once

#include"Object.h"

class bullet : public Object
{

private:
	uint8_t speed = config::bulletSpeed;
	direction dirct = direction::UP;
	uint8_t x = 0, y = 0;

public:

	bullet()
	{
		
	}
	~bullet()
	{

	}

	bool bulletTransmit(direction dirct, uint8_t x, uint8_t y) {
		switch (dirct)
		{
		case UP:
			if (x > 0)
			{
				x -= speed;
			}
			else
				return false;
			break;
		case LEFT:
			if (y>0)
			{
				y -= speed;
			}
			else
				return false;
			break;
		case DOWN:
			if (x < config::winHeight)
			{
				x += speed;
			}
			else
				return false;
			break;
		case RIGHT:
			if (y < config::winWidth - config::rightBlockW)
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

	virtual void blit(SDL_Surface* surface) override {
			
	}

};


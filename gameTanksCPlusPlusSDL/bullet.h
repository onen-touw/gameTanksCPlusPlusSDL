#pragma once

#include"Object.h"
#include"loadingImages.h"

class bullet : public Object, private loadingImages
{

private:
	uint8_t speed = config::bulletSpeed;
	direction dirct = direction::UP;
	uint16_t x = 0, y = 0;

	uint8_t bXSize = 10;			///px 
	uint8_t bYSize = 20;			///px 

	std::vector<imagePath>bulletImagesPathVector = {			/// перенести куда нить
		{"./image/tank/bullets/up.png", direction::UP},
		{"./image/tank/bullets/right.png", direction::RIGHT},
		{"./image/tank/bullets/down.png", direction::DOWN},
		{"./image/tank/bullets/left.png", direction::LEFT},
	};

public:

	bullet(bulletStruct bs): dirct(bs.direct), x(bs.x), y(bs.y)
	{
		this->loadImages()
	}
	~bullet()
	{

	}

	/// return true if the bullet died
	bool bulletTransmit() {
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
		SDL_Rect rc = {};
		if (dirct == UP || dirct == DOWN)
		{
			rc = { x - bXSize / 2, y - bYSize / 2, bXSize, bYSize };
		}
		else
		{
			rc = { x - bYSize / 2, y - bXSize / 2, bYSize, bXSize };
		}
		SDL_BlitScaled(images[dirct], NULL, surface, &rc);
	}

};


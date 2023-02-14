#pragma once

#include"Object.h"
#include"bullet.h"

class Tanks : public Object
{
public:

protected:
	direction dirct = direction::RIGHT;

	uint8_t posInFldI = 0;
	uint8_t posInFldJ = 0;
	
	uint16_t posX = 0;
	uint16_t posY = 0;

	bool isBullet = false;

	bullet* tBullet = nullptr;

	uint8_t speed = config::tankSpeed;

	std::vector<SDL_Surface*>images = {};
	std::vector<SDL_Surface*>bulletImages = {};

	uint8_t tempCountBulet = 0;

public:
	Tanks(uint8_t posInFldI, uint8_t posInFldJ , std::vector<SDL_Surface*>vImg, std::vector<SDL_Surface*>bulletImages)
		: posInFldI(posInFldI), posInFldJ(posInFldJ), images(vImg), bulletImages(bulletImages){}

	virtual ~Tanks(){
		if (tBullet != nullptr)
		{
			delete tBullet;
		}
	}

	virtual void action(std::vector<std::vector<cell>> V, SDL_Event = {}) = 0;

	bool isShot() const {
		return tBullet != nullptr ? true : false;
	}

	/// without checking for walls and checking for tanks
	void bulletHandler() {
		if (isShot())
		{
			if (!tBullet->bulletTransmit()) {
				delete tBullet;
				tBullet = nullptr;
			} 
			else std::cout << "bullet is handling\n";
		}
	}

	virtual void blit(SDL_Surface* surface) final {

		if (isShot())
		{
			tBullet->blit(surface,  bulletImages[tBullet->dirct]);
		}

		SDL_Rect rc = { posInFldJ * cellPxSize , posInFldI * cellPxSize, cellPxSize, cellPxSize };
		SDL_BlitScaled(images[dirct], NULL, surface, &rc);
	}

};

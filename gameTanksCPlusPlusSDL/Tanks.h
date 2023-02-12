#pragma once

#include"Object.h"
#include"loadingImages.h"

class Tanks : public Object, public loadingImages
{
public:
	

protected:
	direction dirct = direction::RIGHT;

	uint8_t posInFldI = 0;
	uint8_t posInFldJ = 0;
	
	uint16_t posX = 0;
	uint16_t posY = 0;

	bool isBullet = false;

	uint8_t speed = config::tankSpeed;

public:
	Tanks(uint8_t posInFldI, uint8_t posInFldJ): posInFldI(posInFldI), posInFldJ(posInFldJ){}
	virtual ~Tanks(){}

	virtual void action(std::vector<std::vector<cell>> V, SDL_Event = {}) = 0;

	bool isShot() {
		return isBullet;
	}

	virtual void blit(SDL_Surface* surface) final {
		SDL_Rect rc = { posInFldJ * cellPxSize , posInFldI * cellPxSize, cellPxSize, cellPxSize };
		SDL_BlitScaled(images[dirct], NULL, surface, &rc);
	}

	bulletStruct getDataForBullet() {
		return { static_cast<uint16_t>(posInFldJ * cellPxSize),
			static_cast<uint16_t>(posInFldI * cellPxSize), dirct };
	}

};

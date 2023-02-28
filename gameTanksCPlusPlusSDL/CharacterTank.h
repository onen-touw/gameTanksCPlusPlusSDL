#pragma once

#include "Tanks.h"

class CharacterTank : public Tanks
{

public:

	CharacterTank(uint8_t i, uint8_t j, std::vector<SDL_Surface*>vImg, std::vector<SDL_Surface*>bImg): Tanks(i,j, vImg, bImg){}

	virtual ~CharacterTank() override {

	}

	virtual void action(std::vector<std::vector<cell>> &V, SDL_Event event = {}) override {
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
		{
			if (this->dirct!=UP) dirct = UP;
			else
			{
				if (posInFldI > 0 && !V[posInFldI - 1ull][posInFldJ].obj)
				{
					--posInFldI;
				}
			}
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
		{
			if (this->dirct != DOWN) dirct = DOWN;
			else
			{
				if (posInFldI < config::cellsHCount-1 && !V[posInFldI + 1ull][posInFldJ].obj)
				{
					++posInFldI;
				}
			}
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
		{
			if (this->dirct != LEFT)this->dirct = LEFT;
			else
			{
				if (posInFldJ > 0 && !V[posInFldI ][posInFldJ - 1ull].obj)
				{
					--posInFldJ;
				}
			}
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
		{
			if (this->dirct != RIGHT) this->dirct = RIGHT;
			else
			{
				if (posInFldJ < config::cellsWCount - 1 && !V[posInFldI][posInFldJ + 1ull].obj)
				{
					++posInFldJ;
				}
			}
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		{
			if (!isShot())
			{
				tBullet = new bullet(dirct, posInFldJ * cellPxSize, posInFldI * cellPxSize);
				std::cout << "bullet is flying\n";
			}
		}
	}


};

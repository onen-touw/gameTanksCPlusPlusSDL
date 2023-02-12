#pragma once

#include "Tanks.h"

class CharacterTank : public Tanks
{

private:
	std::vector<imagePath>TanksImagesPathVector = {
		{"./image/tank/character/up.png", direction::UP},
		{"./image/tank/character/right.png", direction::RIGHT},
		{"./image/tank/character/down.png", direction::DOWN},
		{"./image/tank/character/left.png", direction::LEFT},
	};

public:

	CharacterTank(int i, int j): Tanks(i,j){
		loadImages(TanksImagesPathVector);
	}

	virtual ~CharacterTank() override {

	}

	virtual void action(std::vector<std::vector<cell>> V, SDL_Event event = {}) override {
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
			if (!isBullet) isBullet = true;
		}
	}


};

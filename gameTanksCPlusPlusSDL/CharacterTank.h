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
	virtual void action(SDL_Event event = {}) override {
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
		{
			if (this->dirct!=UP)
			{
				dirct = UP;
			}
			else
			{
				if (posInFldI > 0)
				{
					--posInFldI;
				}
			}
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
		{
			if (this->dirct != DOWN)
			{
				dirct = DOWN;
			}
			else
			{
				if (posInFldI < config::cellsHCount-1)
				{
					++posInFldI;
				}
			}
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
		{
			if (this->dirct != LEFT)
			{
				this->dirct = LEFT;
			}
			else
			{
				if (posInFldJ > 0)
				{
					--posInFldJ;
				}
			}
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
		{
			if (this->dirct != RIGHT)
			{
				this->dirct = RIGHT;
			}
			else
			{
				if (posInFldJ < config::cellsWCount - 1)
				{
					++posInFldJ;
				}
			}
		}
	}

	CharacterTank(int i, int j): Tanks(i,j){
		loadImages(TanksImagesPathVector);
	}
	virtual ~CharacterTank() override {

	}



private:

};

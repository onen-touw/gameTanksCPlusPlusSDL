#pragma once

#include "Tanks.h"

class botTT : public Tanks
{
private:
	std::vector<imagePath>TanksImagesPathVector = {
		{"./image/tank/botTT/up.png", direction::UP},
		{"./image/tank/botTT/right.png", direction::RIGHT},
		{"./image/tank/botTT/down.png", direction::DOWN},
		{"./image/tank/botTT/left.png", direction::LEFT},
	};
public:


	botTT(int i, int j): Tanks(i,j){

		/// main
		//this->dirct = direction::LEFT;
		///temp
		dirct = direction::UP;

		loadImages(TanksImagesPathVector);

#ifdef DEBUG
		std::cout << "botTT::constructor\n";
#endif // DEBUG

	}
	virtual ~botTT() override
	{
#ifdef DEBUG
		std::cout << "botTT::deconstructor\n";
#endif // DEBUG
	}

	virtual void action(std::vector<std::vector<cell>> V, SDL_Event event = {}) override {
		/// AI TTbot 
		if (this->posInFldI > 0)
		{
			if (this->dirct != UP)
			{
				this->dirct = UP;
			}
			else
			{
				--this->posInFldI;
			}
		}
	}

};


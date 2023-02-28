#pragma once

#include "Tanks.h"

class BotLT	: public Tanks
{

public:
	BotLT(uint8_t i, uint8_t j, std::vector<SDL_Surface*>vImg, std::vector<SDL_Surface*>bImg) : Tanks(i, j, vImg, bImg) {

		/// main
		//this->dirct = direction::LEFT;
		///temp
		dirct = direction::UP;

	#ifdef DEBUG
		std::cout << "botTT::constructor\n";
	#endif // DEBUG
	}

	virtual ~BotLT() override
	{
	#ifdef DEBUG
		std::cout << "botTT::deconstructor\n";
	#endif // DEBUG
	}


	virtual void action(std::vector<std::vector<cell>> &V, SDL_Event) override {

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


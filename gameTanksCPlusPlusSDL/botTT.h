#pragma once

#include "Tanks.h"

class botTT : public Tanks
{
private:
	
public:


	botTT(int i, int j, std::vector<SDL_Surface*>vImg): Tanks(i,j, vImg){

		/// main
		//this->dirct = direction::LEFT;
		///temp
		dirct = direction::UP;

		//loadImages(TanksImagesPathVector);

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


#pragma once

#include "Tanks.h"

class botTT : public Tanks
{
public:


	botTT(uint8_t i, uint8_t j, std::vector<SDL_Surface*>vImg, std::vector<SDL_Surface*>bImg): Tanks(i,j, vImg, bImg){

		dirct = direction::UP;

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

	//virtual void action(std::vector<std::vector<cell>> &V, SDL_Event event = {}) override {
	//}

};


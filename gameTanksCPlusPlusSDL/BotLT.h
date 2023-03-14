#pragma once

#include "Tanks.h"

class BotLT	: public Tanks
{

public:
	BotLT(point position, std::vector<SDL_Surface*>vImg, std::vector<SDL_Surface*>bImg) : Tanks(position, vImg, bImg) {
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

};


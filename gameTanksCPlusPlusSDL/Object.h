#pragma once

#include"globals.h"

class Object
{
protected:
	uint8_t cellPxSize = config::cellSize;
public:

	Object() {

#ifdef DEBUG
		std::cout << static_cast<int>(this->cellPxSize) << "\n";
#endif // DEBUG

	}

	virtual ~Object(){}

	virtual void blit(SDL_Surface*) = 0;
};







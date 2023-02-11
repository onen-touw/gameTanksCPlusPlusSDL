#pragma once

#include"globals.h"

class Object
{
protected:
	uint8_t cellPxSize = 0;
public:

	Object() : cellPxSize(config::cellSize) {

#ifdef DEBUG
		std::cout << static_cast<int>(this->cellPxSize) << "\n";
#endif // DEBUG

	}

	virtual ~Object()
	{

	}

	virtual void blit() = 0;
};







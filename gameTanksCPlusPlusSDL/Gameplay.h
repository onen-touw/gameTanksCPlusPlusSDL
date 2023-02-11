#pragma once

#include "Field.h"
#include"baseGameClass.h"

class Gameplay : private baseGameClass
{
private:

	Field f; 
	bool game = true;
	SDL_Event event = {};

public:
	Gameplay() {
		initModuls();
	}
	~Gameplay() {
#ifdef DEBUG
		std::cout << "Gameplay::deconstructor\n";
#endif // DEBUG
	}

	void loop() {
		while (this->game)
		{
			f.blit();
			SDL_UpdateWindowSurface(this->win);
		}
	}

};


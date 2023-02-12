#pragma once

#include"Field.h"
#include"baseGameClass.h"
#include"CharacterTank.h"

class Gameplay : private baseGameClass
{
private:

	Field* field= nullptr;

	std::vector<Tanks*> TanksV = {};

	bool game = true;
	SDL_Event event = {};

public:
	Gameplay() {
		initModuls();
		field = new Field();
		TanksV.push_back(new CharacterTank(5, 5));
	}
	~Gameplay() {

		delete this->field;

#ifdef DEBUG
		std::cout << "Gameplay::deconstructor\n";
#endif // DEBUG
	}

	void loop() {
		while (this->game)
		{
			SDL_PollEvent(&event);

			if (event.type == SDL_QUIT || errors::errorStatus)
			{
				this->game = false;
				return;
			}

			field->blit(this->surface);
			TanksV[0]->action(this->event);

			TanksV[0]->blit(this->surface);
			/*for (int i = 0; i < obj.size(); i++)
			{
				obj[i]->blit(this->surface);
			}*/


			SDL_UpdateWindowSurface(this->win);

			SDL_Delay(1000 / 60);
		}
	}

};


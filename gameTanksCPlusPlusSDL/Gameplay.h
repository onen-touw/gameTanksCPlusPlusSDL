#pragma once

#include"Field.h"
#include"baseGameClass.h"
#include"CharacterTank.h"
#include"botTT.h"

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
		loadResourses();
		field = new Field("lvl1.txt", fieldImages);

		TanksV.push_back(new CharacterTank(5, 5, TankCharacterImages, bulletImages));

		TanksV.push_back(new botTT(24, 7, tankTTImages, bulletImages));
		TanksV.push_back(new botTT(24, 10, tankTTImages, bulletImages));
		TanksV.push_back(new botTT(24, 15, tankTTImages, bulletImages));


		game = !errors::errorStatus ? true : false;
	}
	~Gameplay() {

		delete this->field;

#ifdef DEBUG
		std::cout << "Gameplay::deconstructor\n";
#endif // DEBUG
	}

	void loop() {
		while (this->game )
		{
			SDL_PollEvent(&event);

			if (event.type == SDL_QUIT || errors::errorStatus)
			{
				this->game = false;
				return;
			}

			field->blit(this->surface);

			/// tanks actions
			for (size_t i = 0; i < TanksV.size(); ++i)
			{
				TanksV[i]->action( field->getField(), this->event);
				TanksV[i]->bulletHandler();
				TanksV[i]->blit(this->surface);

			}


			SDL_UpdateWindowSurface(this->win);
			SDL_Delay(1000 / config::FPS);
		}
	}

};


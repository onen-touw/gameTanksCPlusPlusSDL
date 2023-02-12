#pragma once

#include"Field.h"
#include"baseGameClass.h"
#include"CharacterTank.h"
#include"botTT.h"
#include"bullet.h"

class Gameplay : private baseGameClass
{
private:

	Field* field= nullptr;

	std::vector<Tanks*> TanksV = {};
	std::vector<bullet*>bullets = {};///?

	bool game = true;
	SDL_Event event = {};

public:
	Gameplay() {
		initModuls();
		field = new Field("lvl1.txt");

		TanksV.push_back(new CharacterTank(5, 5));

		TanksV.push_back(new botTT(24, 7));
		TanksV.push_back(new botTT(24, 10));
		TanksV.push_back(new botTT(24, 15));

		bullets.resize(TanksV.size());
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

			for (size_t i = 0; i < TanksV.size(); ++i)
			{
				if (TanksV[i]->isShot())
				{
					this->bullets[i] = new bullet(TanksV[i]->getDataForBullet());
					std::cout << "shot\n";
				}

				TanksV[i]->action( field->getField(), this->event);
				TanksV[i]->blit(this->surface);

			}


			SDL_UpdateWindowSurface(this->win);
			SDL_Delay(1000 / config::FPS);
		}
	}

};


#pragma once

#include"Field.h"
#include"baseGameClass.h"
#include"CharacterTank.h"
#include"botTT.h"
#include"BotLT.h"

#include"StartWindow.h"
#include "testClass.h"
#include "aboutWin.h"
#include "StatisticWin.h"


class Gameplay : private baseGameClass
{
private:

	Field* field= nullptr;
	Object* startWindow = nullptr;
	Object* testCl = nullptr;

	std::vector<Tanks*> TanksV = {};
	std::vector<Object*> sceneObject = {};

	bool game = true;
	SDL_Event event = {};

public:
	Gameplay() {
		initModuls();
		loadResourses();

		/// transmit in special function
		field = new Field("lvl1.txt", fieldImages);
		sceneObject.push_back(field);

		TanksV.push_back(new CharacterTank(5, 5, TankCharacterImages, bulletImages));
		sceneObject.push_back(TanksV[0]);

		TanksV.push_back(new botTT(24, 7, tankTTImages, bulletImages));
		sceneObject.push_back(TanksV[1]);

		TanksV.push_back(new botTT(24, 10, tankTTImages, bulletImages));
		sceneObject.push_back(TanksV[2]);

		TanksV.push_back(new botTT(24, 15, tankTTImages, bulletImages));
		sceneObject.push_back(TanksV[3]);

		TanksV.push_back(new BotLT(24, 25, tankLTImages, bulletImages));
		sceneObject.push_back(TanksV[4]);

		startWindow = new StartWindow( menuImages, font);
		testCl = new /*testClass(menuImages, font)*//*StartWindow*/StatisticWin(menuImages, font);

		game = !errors::errorStatus ? true : false;
	}
	~Gameplay() {

		delete this->field;

#ifdef DEBUG
		std::cout << "Gameplay::deconstructor\n";
#endif // DEBUG
	}

	void loop() {

		game = !errors::errorStatus ? true : false;

		while (this->game )
		{
			SDL_PollEvent(&event);

			if (event.type == SDL_QUIT)
			{
				this->game = false;
				return;
			}

			/// tanks actions
			for (size_t i = 0; i < TanksV.size(); ++i)
			{
				TanksV[i]->action( field->getField(), this->event);
				TanksV[i]->bulletHandler();
			}
			testCl->blit(surface);
			
			for (auto& el : sceneObject)
			{
				//el->blit(surface);
			}

			SDL_UpdateWindowSurface(this->win);
			SDL_Delay(1000 / config::FPS);
		}
	}

};


#pragma once

#include"Field.h"
#include"baseGameClass.h"
#include"CharacterTank.h"
#include"botTT.h"
#include"BotLT.h"

#include"StartWindow.h"
//#include "testClass.h"
#include "aboutWin.h"
#include "StatisticWin.h"


class Gameplay : private baseGameClass
{
private:

	Field* field= nullptr;
	Object* startWindow = nullptr;
	Object* testCl = nullptr;
	CharacterTank* chTank = nullptr;

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

		chTank = new CharacterTank(5, 5, TankCharacterImages, bulletImages);
		sceneObject.push_back(chTank);

		TanksV.push_back(new botTT(24, 7, tankTTImages, bulletImages));
		sceneObject.push_back(TanksV[0]);

		/*TanksV.push_back(new botTT(24, 15, tankTTImages, bulletImages));
		sceneObject.push_back(TanksV[1]);*/
		

		//TanksV.push_back(new botTT(24, 10, tankTTImages, bulletImages));
		//sceneObject.push_back(TanksV[2]);

		//TanksV.push_back(new botTT(24, 15, tankTTImages, bulletImages));
		//sceneObject.push_back(TanksV[3]);

		//TanksV.push_back(new BotLT(24, 25, tankLTImages, bulletImages));
		//sceneObject.push_back(TanksV[4]);

		//startWindow = new StartWindow( menuImages, font);
		//testCl = new /*testClass(menuImages, font)*//*StartWindow*/StatisticWin(menuImages, font);

		game = !errors::errorStatus ? true : false;
	}
	~Gameplay() {

		delete this->field;

#ifdef DEBUG
		std::cout << "Gameplay::deconstructor\n";
#endif // DEBUG
	}

private:
	uint32_t time1 = 0;

public:
	void loop() {

		//game = !errors::errorStatus ? true : false;

		//TanksV[1]->generateWay({ 5,5 }, { 24, 7 }, field->getField());
		time1 = SDL_GetTicks();

		while (this->game )
		{
			SDL_PollEvent(&event);

			if (event.type == SDL_QUIT)
			{
				this->game = false;
				return;
			}

			/// tanks actions
			chTank->action(field->getField(), this->event);
			chTank->bulletHandler();

			if (SDL_GetTicks() - time1 > 200)
			{
				for (size_t i = 0; i < TanksV.size(); ++i)
				{
					TanksV[i]->generateWay(chTank->getPosition(), field->getField());
					std::cout << TanksV[i]->getPosition().i << " x " << TanksV[i]->getPosition().j << "\n";
				}
				time1 = SDL_GetTicks();
			}
			
			for (auto& el : sceneObject)
			{
				el->blit(surface);
			}

			SDL_UpdateWindowSurface(this->win);
			SDL_Delay(1000 / config::FPS);
		}
	}

};


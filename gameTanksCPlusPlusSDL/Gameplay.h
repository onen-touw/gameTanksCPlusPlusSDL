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
		field = new Field("lvl2.txt", fieldImages);
		sceneObject.push_back(field);
		if (!field->getMapLoadingStatus())
		{
			errorStatus = MAP_LOADING_ERROR;
		}

		chTank = new CharacterTank(5, 5, TankCharacterImages, bulletImages);

		TanksV.push_back(new botTT(23, 7, tankTTImages, bulletImages));
		sceneObject.push_back(TanksV[0]);

		TanksV.push_back(new botTT(23, 15, tankTTImages, bulletImages));
		sceneObject.push_back(TanksV[1]);
		
		TanksV.push_back(new botTT(23, 11, tankTTImages, bulletImages));
		sceneObject.push_back(TanksV[2]);

		sceneObject.push_back(chTank);

		

		//startWindow = new StartWindow( menuImages, font);
		//testCl = new /*testClass(menuImages, font)*//*StartWindow*/StatisticWin(menuImages, font);

		game = !errorStatus ? true : false;
	}
	~Gameplay() {

		delete this->field;

#ifdef DEBUG
		std::cout << "Gameplay::deconstructor\n";
#endif // DEBUG
	}

private:
	uint32_t deltaTime = 0;
	uint32_t moveTanksDelay = config::moveTanksDelay;

	std::function<void(size_t)>DeleteTanks = [&](size_t index) {
		sceneObject.erase(sceneObject.begin() + ++index);
	};

public:

	ErrorsCodes getErrorStatus() const { return errorStatus; }


	void loop() {

		deltaTime = SDL_GetTicks();
		
		while (this->game)
		{
			SDL_PollEvent(&event);

			if (event.type == SDL_QUIT)
			{
				this->game = false;
				return;
			}
			//bool update = false;
			//if () update = true;
			/// tanks actions
			chTank->bulletHandler(field->getField(), TanksV, DeleteTanks);
			chTank->action(field->getField(), this->event);

			for (auto& el : TanksV)
			{
				el->bulletHandler(field->getField(), TanksV, nullptr, chTank->getPosition());
			}

			if (SDL_GetTicks() - deltaTime > moveTanksDelay)
			{
				chTank->generateWayMap(field->getField(), TanksV);
				for (auto& el : TanksV)
				{
					el->botShotActions(chTank->getPosition(), field->getField());
					el->NextStep(chTank->getWaveMap());
				}
				deltaTime = SDL_GetTicks();
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


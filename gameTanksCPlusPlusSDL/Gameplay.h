#pragma once

#include"Field.h"
#include"baseGameClass.h"
#include"CharacterTank.h"
#include"botTT.h"
#include"BotLT.h"

#include"MenuHandler.h"
#include"RightPanel.h"



class Gameplay : private baseGameClass
{
private:

	Field* field= nullptr;
	CharacterTank* chTank = nullptr;
	RightPanel* rightPanel = nullptr;

	MenuHandler* menuHand = nullptr;

	std::vector<Tanks*> TanksV = {};
	std::vector<Object*> sceneObject = {};

	bool game = true;
	SDL_Event event = {};

	gameStates currentGameState = gameStates::HelloWin;

public:
	Gameplay() {
		initModuls();
		loadResourses();
		if (!errorStatus)
		{
			deltaTime = SDL_GetTicks();
			menuHand = new MenuHandler(menuImages, font);
			menuHand->startingWin();
		}
		else
		{
			game = false;
		}
	}
	~Gameplay() {
		clearPointerMemory();

#ifdef DEBUG
		std::cout << "Gameplay::deconstructor\n";
#endif // DEBUG
	}

private:
	uint32_t deltaTime = 0;
	uint32_t moveTanksDelay = config::moveTanksDelay;
	uint8_t botTanksCount = 0;

	std::function<void(size_t)>DeleteTanks = [&](size_t index) {
		sceneObject.erase(sceneObject.begin() + ++index);
	};

	void clearPointerMemory() {
		if (field != nullptr) delete field;
		if (chTank != nullptr) delete chTank;
		if (rightPanel != nullptr) delete rightPanel;
	}

	std::function<void(std::string)>BuildGame = [&](std::string map) {
		botTanksCount = 0;
		TanksV.clear();
		sceneObject.clear();

		clearPointerMemory();

		field = new Field(map, fieldImages);
		if (!field->getMapLoadingStatus()) { errorStatus = MAP_LOADING_ERROR; return; }

		sceneObject.push_back(field);

		chTank = new CharacterTank(field->getUnitPosition()[0], TankCharacterImages, bulletImages);

		for (size_t i = 1; i < field->getUnitPosition().size(); ++i)
		{
			TanksV.push_back(new botTT(field->getUnitPosition()[i], tankTTImages, bulletImages));
			sceneObject.push_back(TanksV[i-1]);
			++botTanksCount;
		}
		sceneObject.push_back(chTank);

		rightPanel = new RightPanel(menuImages, font, botTanksCount);
		rightPanel->setText();
		sceneObject.push_back(rightPanel);
	};

public:

	ErrorsCodes getErrorStatus() const { return errorStatus; }

	void handlingHelloWin() {
		while (this->game)
		{
			SDL_PollEvent(&event);

			if (event.type == SDL_QUIT)
			{
				this->game = false;
				return;
			}
			if (event.type == SDL_KEYDOWN)
			{
				currentGameState = gameStates::MenuHandling; 
				menuHand->openMenu(true);
				return;
			}
			menuHand->blit(surface);
			SDL_UpdateWindowSurface(this->win);
			SDL_Delay(1000 / config::FPS);
		}
	}

	void loop() {

		
		while (this->game)
		{
			SDL_PollEvent(&event);

			if (event.type == SDL_QUIT || currentGameState == Quit)
			{
				this->game = false;
				return;
			}
			if (currentGameState == MenuHandling)
			{
				menuHand->handler(event, currentGameState, BuildGame);
				menuHand->blit(surface);
			}
			else if (currentGameState == Playing)
			{
				/// tanks actions
				if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
				{
					int x = 0, y = 0;
					SDL_GetMouseState(&x, &y);
					if (rightPanel->checkButtonClick(x, y) == 0)
					{
						currentGameState = MenuHandling;
						menuHand->openMenu();
					}
				}

				if (chTank->getKillCount() == botTanksCount)
				{
					currentGameState = MenuHandling;
					menuHand->openResultWin(true);
				}

				if (chTank->bulletHandler(field->getField(), TanksV, DeleteTanks)) rightPanel->setText(chTank->getKillCount());
				chTank->action(field->getField(), this->event);

				for (auto& el : TanksV)
				{
					if (el->bulletHandler(field->getField(), TanksV, nullptr, chTank->getPosition()))
					{
						currentGameState = MenuHandling;
						menuHand->openResultWin(false);
					}	
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
			}

			SDL_UpdateWindowSurface(this->win);
			SDL_Delay(1000 / config::FPS);
		}
	}

};


#pragma once

#include "Tanks.h"

class CharacterTank : public Tanks
{
private: uint8_t killCounter = 0;

public:

	CharacterTank(point position, std::vector<SDL_Surface*>vImg, std::vector<SDL_Surface*>bImg)
		:Tanks(position, vImg, bImg){
		vizitedElement.reserve(200);
		toVizit.reserve(200);
		waveAlg.resize(config::cellsHCount);
		for (size_t i = 0; i < waveAlg.size(); ++i)
		{
			waveAlg[i].resize(config::cellsWCount, 0);
		}
	}

	virtual ~CharacterTank() override {

	}

private:
	std::vector<point> Neighbors(point p, std::vector<std::vector<cell>>& V,
		std::vector<std::vector<int16_t>>& wave) {

		std::vector<point> neighbours = {};
		point pp = {};

		if (p.i > 0)
		{
			if (!wave[p.i - 1ll][p.j])
			{
				if (!V[p.i - 1ll][p.j].obj)
				{
					pp = { p.i - 1 , p.j };
					neighbours.push_back(pp);
				}
				else
				{
					wave[p.i - 1ll][p.j] = -1;
				}
			}
		}
		if (p.i + 1ll < V.size())
		{
			if (!wave[p.i + 1ll][p.j])
			{
				if (!V[p.i + 1ll][p.j].obj)
				{
					pp = { p.i + 1 , p.j };
					neighbours.push_back(pp);
				}
				else
				{
					wave[p.i + 1ll][p.j] = -1;
				}
			}
		}

		if (p.j > 0)
		{
			if (!wave[p.i][p.j - 1ll])
			{
				if (!V[p.i][p.j - 1ll].obj)
				{
					pp = { p.i , p.j - 1 };
					neighbours.push_back(pp);
				}
				else
				{
					wave[p.i][p.j - 1ll] = -1;
				}
			}
		}
		if (p.j + 1ll < V[0].size())
		{
			if (!wave[p.i][p.j + 1ll])
			{
				if (!V[p.i][p.j + 1ll].obj)
				{
					pp = { p.i , p.j + 1 };
					neighbours.push_back(pp);
				}
				else
				{
					wave[p.i][p.j + 1ll] = -1;
				}
			}
		}

		return neighbours;
	}

	void resetToZeroWaveMap() {
		for (auto& v : waveAlg) {
			std::fill(v.begin(), v.end(), 0);
		}
	}

private:
	std::vector<std::vector<int16_t>> waveAlg;
	std::vector<point> vizitedElement = {};
	std::vector<point> toVizit = {};


public:
	void generateWayMap(/*point characterPos,*/  std::vector<std::vector<cell>>& V, std::vector<Tanks*>&tanks) {
		
		uint16_t stepCost = 1;

		resetToZeroWaveMap();
		waveAlg[posInFldI][posInFldJ] = -1;

		point tmp = {};
		for (auto& el : tanks)
		{
			tmp = el->getPosition();
			waveAlg[tmp.i][tmp.j] = -1;
		}

		vizitedElement.push_back({ posInFldI , posInFldJ});
		do
		{
			toVizit.clear();

			for (int i = 0; i < vizitedElement.size(); ++i)
			{
				std::vector<point> tpm = Neighbors(vizitedElement[i], V, waveAlg);
				if (!tpm.empty())
				{
					for (int j = 0; j < tpm.size(); ++j)
					{
						toVizit.push_back(tpm[j]);
					}
				}
			}

			for (int i = 0; i < toVizit.size(); ++i)
			{
				point tmp = toVizit[i];

				if (waveAlg[tmp.i][tmp.j] == 0)
				{
					waveAlg[tmp.i][tmp.j] = stepCost;
					vizitedElement.push_back(tmp);
				}
			}
			++stepCost;
		} while (!toVizit.empty());

		vizitedElement.clear();
	}

	std::vector<std::vector<int16_t>>& getWaveMap() { return this->waveAlg; }

	uint8_t getKillCount() const { return killCounter; }

	void action(std::vector<std::vector<cell>> &V, SDL_Event event) {
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
		{
			if (this->dirct!=UP) dirct = UP;
			else
			{
				if (posInFldI > 0 && !V[posInFldI - 1ull][posInFldJ].obj)
				{
					--posInFldI;
				}
			}
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
		{
			if (this->dirct != DOWN) dirct = DOWN;
			else
			{
				if (posInFldI < config::cellsHCount-1 && !V[posInFldI + 1ull][posInFldJ].obj)
				{
					++posInFldI;
				}
			}
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
		{
			if (this->dirct != LEFT)this->dirct = LEFT;
			else
			{
				if (posInFldJ > 0 && !V[posInFldI][posInFldJ - 1ull].obj)
				{
					--posInFldJ;
				}
			}
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
		{
			if (this->dirct != RIGHT) this->dirct = RIGHT;
			else
			{
				if (posInFldJ < config::cellsWCount - 1 && !V[posInFldI][posInFldJ + 1ull].obj)
				{
					++posInFldJ;
				}
			}
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		{
			if (!isShot())
			{
				tBullet = new bullet(dirct, posInFldJ * cellPxSize, posInFldI * cellPxSize);
				tBullet->setDeathPoint(V, posInFldI, posInFldJ);
			#ifdef DEBUG
				std::cout << "bullet is flying\n";
			#endif // DEBUG

			}
		}
	}


	bool bulletHandler(std::vector<std::vector<cell>>& field, std::vector<Tanks*>& tanks,
		std::function<void(size_t)>delFoo)
	{
		if (isShot())
		{
			if (!tBullet->bulletTransmit(field))
			{
				removeBullet();
			#ifdef DEBUG
				std::cout << "bullet dead\n";
			#endif // DEBUG
				return false;
			}
			else
			{
				point tankTmpPos = {};
				point bulletTmpPos = tBullet->getPositionCell();

				for (size_t i = 0; i < tanks.size(); ++i)
				{
					if (tanks[i]->getPosition() == bulletTmpPos)
					{
						std::cout << "char hits bos\n";
						tanks.erase(tanks.begin() + i);
						delFoo(i);
						++killCounter;
						removeBullet();
						return true;
					}
				}
			}
		}
		return false;
	}

};

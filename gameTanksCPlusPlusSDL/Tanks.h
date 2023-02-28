#pragma once

#include"Object.h"
#include"bullet.h"

class Tanks : public Object
{
public:

protected:
	direction dirct = direction::RIGHT;

	uint8_t posInFldI = 0;
	uint8_t posInFldJ = 0;
	
	bullet* tBullet = nullptr;

	uint8_t speed = config::tankSpeed;

	std::vector<SDL_Surface*>images = {};
	std::vector<SDL_Surface*>bulletImages = {};

public:
	Tanks(uint8_t posInFldI, uint8_t posInFldJ , std::vector<SDL_Surface*>vImg, std::vector<SDL_Surface*>bulletImages)
		: posInFldI(posInFldI), posInFldJ(posInFldJ), images(vImg), bulletImages(bulletImages){
		vizitedElement.reserve(alIterationMax * 4ll);
		toVizit.reserve(alIterationMax * 4ll);
	}

	virtual ~Tanks(){
		if (tBullet != nullptr)
		{
			delete tBullet;
		}
	}

	virtual void action(std::vector<std::vector<cell>>& V, SDL_Event = {}) = 0;

	uint8_t distanse(point& p1, point& p2) {
		return fabs(p2.i - p1.i) + fabs(p2.j - p1.j);
	}

private:
	std::vector<point> Neighbors(point p, std::vector<std::vector<cell>>&V, 
		std::vector<std::vector<int16_t>>& wave) {

		std::vector<point> neighbours = {};
		point pp = {};

		if (p.i > 0)
		{
			if (!wave[p.i-1ll][p.j])
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
		if (p.i +1ll < V.size())
		{
			if (!wave[p.i+1ll][p.j])
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
			if (!wave[p.i][p.j-1ll])
			{
				if (!V[p.i][p.j - 1ll].obj)
				{
					pp = { p.i , p.j - 1 };
					neighbours.push_back(pp);
				}
				else
				{
					wave[p.i ][p.j - 1ll] = -1;
				}
			}
		}
		if (p.j + 1ll < V[0].size())
		{
			if (!wave[p.i][p.j+1ll])
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

	void getNextStep(point p ,std::vector<std::vector<int16_t>>& wave) {
		uint16_t min = wave[p.i][p.j];
		point tmp = {};
		if (p.i>0)
		{
			if (wave[p.i - 1ll][p.j]> 3 && wave[p.i - 1ll][ p.j] < min)
			{
				min = wave[p.i - 1ll][p.j];
				tmp = { p.i - 1, p.j };
				dirct = UP;
			}
		}
		if (p.j>0)
		{
			if (wave[p.i][p.j-1ll] > 3 && wave[p.i][p.j-1ll] < min) {
				min = wave[p.i][p.j - 1ll];
				tmp = { p.i, p.j -1};
				dirct = LEFT;
			}
		}
		if (p.i+1ll < wave.size())
		{
			if (wave[p.i+1ll][p.j] > 3 && wave[p.i+1ll][p.j] < min) {
				min = wave[p.i + 1ll][p.j];
				tmp = { p.i + 1, p.j };
				dirct = DOWN;
			}
		}
		if (p.j+1ll < wave[0].size())
		{
			if (wave[p.i ][p.j + 1ll] > 3 && wave[p.i][p.j + 1ll] < min) {
				min = wave[p.i][p.j + 1ll];
				tmp = { p.i, p.j+1 };
				dirct = RIGHT;
			}
		}
		posInFldI = tmp.i;
		posInFldJ = tmp.j;
	}

private:
	std::vector<std::vector<int16_t>> waveAlg;
	std::vector<point> vizitedElement = {};
	std::vector<point> toVizit = {};

	const uint8_t alIterationMax = 30;

public:
	void generateWay(point p1, std::vector<std::vector<cell>>& V) {
		point p2 = { posInFldI, posInFldJ };
		if (distanse(p1, p2) > 1)
		{

			waveAlg.resize(config::cellsHCount);
			for (size_t i = 0; i < waveAlg.size(); i++)
			{
				waveAlg[i].resize(config::cellsWCount);
			}

			uint8_t stepCost = 1;

			vizitedElement.push_back(p1);

			uint16_t TEMP_COUNTER = 0;

			while (waveAlg[p2.i][p2.j] == 0)
			{
				if (++TEMP_COUNTER > alIterationMax)
				{
					return;
				}

				for (int i = 0; i < vizitedElement.size(); ++i)
				{
					std::vector<point> tpm = Neighbors(vizitedElement[i], V, waveAlg);
					if (!tpm.empty())
					{
						for (int j = 0; j < tpm.size(); j++)
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
				toVizit.clear();
			}

			for (size_t i = 0; i < waveAlg.size(); i++)
			{
				for (size_t j = 0; j < waveAlg[0].size(); j++)
				{
					std::cout << waveAlg[i][j] << " ";
				}
				std::cout << "\n";
			}
			getNextStep(p2, waveAlg);
			vizitedElement.clear();
			waveAlg.clear();
		}
		else return;
		//else {
		//	/*for (size_t i = 0; i < 6; ++i)
		//	{
		//		waveAlg[p1.i][i] = 1;
		//	}
		//	for (size_t i = 6; i > 0; --i)
		//	{
		//		waveAlg[p1.i][i] = 1;
		//	}
		//	for (size_t i = 0; i < 6; ++i)
		//	{
		//		waveAlg[i][p1.j] = 1;
		//	}
		//	for (size_t i = 6; i > 0; --i)
		//	{
		//		waveAlg[i][p1.i] = 1;
		//	}*/
		//	return;
		//}
	}

	point getPosition()const { return { posInFldI, posInFldJ }; }

	bool isShot() const {
		return tBullet != nullptr ? true : false;
	}

	/// without checking for walls and checking for tanks
	void bulletHandler(/* field&, Vector<tanks>& */) {
		if (isShot())
		{
			if (!tBullet->bulletTransmit(/* field, Vector<tanks> */)) {
				delete tBullet;
				tBullet = nullptr;
			} 
			else std::cout << "bullet is handling\n";
		}
	}

	virtual void blit(SDL_Surface* surface) final {

		if (isShot())
		{
			tBullet->blit(surface,  bulletImages[tBullet->dirct]);
		}

		SDL_Rect rc = { posInFldJ * cellPxSize , posInFldI * cellPxSize, cellPxSize, cellPxSize };
		SDL_BlitScaled(images[dirct], NULL, surface, &rc);
	}

};

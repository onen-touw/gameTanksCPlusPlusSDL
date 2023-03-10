#pragma once

#include"Object.h"
#include"bullet.h"
#include<functional>

class Tanks : public Object
{
public:

protected:
	direction dirct = direction::RIGHT;

	int16_t posInFldI = 0;
	int16_t posInFldJ = 0;
	
	bullet* tBullet = nullptr;

	std::vector<SDL_Surface*>images = {};
	std::vector<SDL_Surface*>bulletImages = {};

	uint8_t detectionByLenthOfWay = 25;
	uint8_t minimalTargetDistanse = 0;

public:
	Tanks(uint8_t posInFldI, uint8_t posInFldJ , std::vector<SDL_Surface*>vImg, std::vector<SDL_Surface*>bulletImages)
		: posInFldI(posInFldI), posInFldJ(posInFldJ), images(vImg), bulletImages(bulletImages){
	
	}

	virtual ~Tanks(){
		if (tBullet != nullptr)
		{
			delete tBullet;
		}
	}

	//virtual void action(std::vector<std::vector<cell>>& V, SDL_Event = {}) = 0;
private:
	int8_t distanse(point p1) {
		return fabs(p1.i - posInFldI) + fabs(p1.j - posInFldJ);
	}


public:
	void NextStep(std::vector<std::vector<int16_t>>& wave) {
		//if (distanse(charPosition) > detectionRadius) return;
		if (wave[posInFldI][posInFldJ] > detectionByLenthOfWay) return;

		int16_t min = wave[posInFldI][posInFldJ];
		point tmp = {posInFldI , posInFldJ};
		if (posInFldI>0)
		{
			if (wave[posInFldI - 1ll][posInFldJ]> minimalTargetDistanse && wave[posInFldI - 1ll][posInFldJ] < min)
			{
				min = wave[posInFldI - 1ll][posInFldJ];
				tmp = { posInFldI - 1, posInFldJ };
				dirct = UP;
			}
		}
		if (posInFldJ>0)
		{
			if (wave[posInFldI][posInFldJ-1ll] > minimalTargetDistanse && wave[posInFldI][posInFldJ-1ll] < min) {
				min = wave[posInFldI][posInFldJ - 1ll];
				tmp = { posInFldI, posInFldJ -1};
				dirct = LEFT;
			}
		}
		if (posInFldI< wave.size() - 1)
		{
			if (wave[posInFldI+1ll][posInFldJ] > minimalTargetDistanse && wave[posInFldI+1ll][posInFldJ] < min) {
				min = wave[posInFldI + 1ll][posInFldJ];
				tmp = { posInFldI + 1, posInFldJ };
				dirct = DOWN;
			}
		}
		if (posInFldJ< wave[0].size() - 1)
		{
			if (wave[posInFldI ][posInFldJ + 1ll] > minimalTargetDistanse && wave[posInFldI][posInFldJ + 1ll] < min) {
				min = wave[posInFldI][posInFldJ + 1ll];
				tmp = { posInFldI, posInFldJ+1 };
				dirct = RIGHT;
			}
		}
		posInFldI = tmp.i;
		posInFldJ = tmp.j;
	}


	point getPosition() const { return { posInFldI, posInFldJ }; }

	bool isShot() const {
		return tBullet != nullptr ? true : false;
	}

	/// without checking for walls and checking for tanks
	void bulletHandler(std::vector<std::vector<cell>>& field, std::vector<Tanks*> &tanks, std::function<void(size_t)>delFoo) {
		if (isShot())
		{
			if (!tBullet->bulletTransmit(field)) {
			#ifdef DEBUG
				std::cout << "bullet dead\n";
			#endif // DEBUG
				delete tBullet;
				tBullet = nullptr;
			} 
			else
			{
				point tankTmpPos = {};
				point bulletTmpPos = tBullet->getPositionCell();
				for (size_t i = 0; i < tanks.size(); ++i)
				{
					tankTmpPos = tanks[i]->getPosition();
					if (tankTmpPos.i == bulletTmpPos.i && tankTmpPos.j == bulletTmpPos.j)
					{
						std::cout << "hit\n";
						tanks.erase(tanks.begin() + i);
						delFoo(i);
						delete tBullet;
						tBullet = nullptr;
						return;
					}
				}
			}
		}
	}

//protected:
//	void doShot()
//	{
//		if (!isShot())
//		{
//			tBullet = new bullet(dirct, posInFldJ * cellPxSize, posInFldI * cellPxSize);
//			tBullet->setDeathPoint(V, posInFldI, posInFldJ);
//		#ifdef DEBUG
//					std::cout << "bullet is flying\n";
//		#endif // DEBUG
//		}
//	}

	void doShot() {
		///characterPos&, field&, 
		if (!isShot())
		{
			tBullet = new bullet(dirct, posInFldJ * cellPxSize, posInFldI * cellPxSize);
		#ifdef DEBUG
			std::cout << "bullet is flying\n";
		#endif // DEBUG
		}
	}


public:
	virtual void blit(SDL_Surface* surface) final {

		if (isShot())
		{
			tBullet->blit(surface,  bulletImages[tBullet->dirct]);
		}

		SDL_Rect rc = { posInFldJ * cellPxSize , posInFldI * cellPxSize, cellPxSize, cellPxSize };
		SDL_BlitScaled(images[dirct], NULL, surface, &rc);
	}

};

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

	uint8_t detectionByLenthOfWay = config::detectionByLenthOfWay;
	uint8_t minimalTargetDistanse = config::minimalTargetDistanse;
	bool ableToShot = false;


public:
	Tanks(point position , std::vector<SDL_Surface*>vImg, std::vector<SDL_Surface*>bulletImages)
		: posInFldI(position.i), posInFldJ(position.j), images(vImg), bulletImages(bulletImages){
	
	}

	virtual ~Tanks(){
		if (tBullet != nullptr)
		{
			delete tBullet;
		}
	}

private:
	int8_t distanse(point p1) const {
		return abs(p1.i - posInFldI) + abs(p1.j - posInFldJ);
	}


public:
	void NextStep(std::vector<std::vector<int16_t>>& wave) {

		if (wave[posInFldI][posInFldJ] > detectionByLenthOfWay) return;
		if (ableToShot) return;
	
		int16_t min = INT16_MAX;
		int16_t tmpI = 0;
		point tmp = {posInFldI, posInFldJ};
		if (posInFldI>0)
		{
			tmpI = wave[posInFldI - 1ll][posInFldJ];
			if (tmpI > minimalTargetDistanse && tmpI >0 && tmpI < min)
			{
				min = wave[posInFldI - 1ll][posInFldJ];
				tmp = { posInFldI - 1, posInFldJ };
				dirct = UP;
			}
		}
		if (posInFldJ>0)
		{
			tmpI = wave[posInFldI][posInFldJ - 1ll];
			if (tmpI > minimalTargetDistanse && tmpI > 0 && tmpI < min) {
				min = wave[posInFldI][posInFldJ - 1ll];
				tmp = { posInFldI, posInFldJ -1};
				dirct = LEFT;
			}
		}
		if (posInFldI< wave.size() - 1)
		{
			tmpI = wave[posInFldI + 1ll][posInFldJ];
			if (tmpI > minimalTargetDistanse && tmpI > 0 && tmpI < min) {
				min = wave[posInFldI + 1ll][posInFldJ];
				tmp = { posInFldI + 1, posInFldJ };
				dirct = DOWN;
			}
		}
		if (posInFldJ< wave[0].size() - 1)
		{
			tmpI = wave[posInFldI][posInFldJ + 1ll];
			if (tmpI > minimalTargetDistanse && tmpI > 0 && tmpI < min) {
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

	void removeBullet() {
		delete tBullet;
		tBullet = nullptr;
	}

	/// with checking for walls and checking for tanks
	bool bulletHandler(std::vector<std::vector<cell>>& field, std::vector<Tanks*>& tanks, 
		 std::function<void(size_t)>delFoo = nullptr, point charPos = {})
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
				point bulletTmpPos = tBullet->getPositionCell();

				if (charPos == bulletTmpPos)
				{
					std::cout << "bot hits char \n";
					removeBullet();
					return true;
				}
				for (size_t i = 0; i < tanks.size(); ++i)
				{
					if (tanks[i]->getPosition() == bulletTmpPos)
					{
						removeBullet();
						return false;
					}
				}
			}
		}
		return false;
	}

protected:
	void doShot(std::vector<std::vector<cell>>& field)
	{
		if (!isShot())
		{
			tBullet = new bullet(dirct, posInFldJ * cellPxSize, posInFldI * cellPxSize);
			tBullet->setDeathPoint(field, posInFldI, posInFldJ);

		#ifdef DEBUG
					std::cout << "bullet is flying\n";
		#endif // DEBUG
		}
	}

public:
	void botShotActions(point characterPos, std::vector<std::vector<cell>>&field) {
		if (distanse(characterPos) > config::bulletMaxFlyDistance)
		{
			ableToShot = false;
			return;
		}

		if (characterPos.i == posInFldI)
		{
			if (characterPos.j < posInFldJ)
			{
				std::cout << "Bot can shot/ char left\n";
				dirct = LEFT;
				doShot(field);
				ableToShot = true;
				return;
			}
			else
			{
				std::cout << "Bot can shot/ char right\n";
				dirct = RIGHT;
				doShot(field);
				ableToShot = true;
				return;
			}
		}
		else if (characterPos.j == posInFldJ)
		{
			if (characterPos.i < posInFldI)
			{
				std::cout << "Bot can shot/ char upper\n";
				dirct = UP;
				doShot(field);
				ableToShot = true;
				return;
			}
			else
			{
				dirct = DOWN;
				std::cout << "Bot can shot/ char lower\n";
				doShot(field);
				ableToShot = true;
				return;
			}
		}
		ableToShot = false;
		return;
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

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
    point position = {};
    point oldposition = {};
	
	bullet* tBullet = nullptr;

	uint8_t speed = config::tankSpeed;

	std::vector<SDL_Surface*>images = {};
	std::vector<SDL_Surface*>bulletImages = {};

public:
	Tanks(point pos , std::vector<SDL_Surface*>vImg, std::vector<SDL_Surface*>bulletImages)
		: position(pos), oldposition(pos), images(vImg), bulletImages(bulletImages){}

	virtual ~Tanks(){
		if (tBullet != nullptr)
		{
			delete tBullet;
		}
	}

	//virtual void action(std::vector<std::vector<cell>> V, SDL_Event = {}) = 0;

	bool isShot() const {
		return tBullet != nullptr ? true : false;
	}

	/// without checking for walls and checking for tanks
	void bulletHandler() {
		if (isShot())
		{
			if (!tBullet->bulletTransmit()) {
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

    bool SetNextPosEalyGameplay(std::vector<std::vector<cell>>& field)
    {
        srand(time(0));
        uint8_t counter = 0;
        point nextPos;
        uint8_t direction = rand() % direction::DIRECTIONS_TOTAL;
        if (direction == direction::UP)
        {
            if (position.p1 > 0)
            {
                if (field[position.p1 - 1][position.p2].obj == cellObjects::Empty)
                {
                    nextPos = { uint8_t(position.p1 - 1), position.p2 };
                    oldposition = position;
                    position = nextPos;
                    return true;
                }
                else
                {
                    direction = (direction + 1) % direction::DIRECTIONS_TOTAL;
                    counter++;
                }
            }
            else
            {
                direction = (direction + 1) % direction::DIRECTIONS_TOTAL;
                counter++;
            }
        }
        else if (direction == direction::RIGHT)
        {
            if (position.p2 < config::cellsWCount - 1)
            {
                if (field[position.p1][position.p2 + 1].obj == cellObjects::Empty)
                {
                    nextPos = { position.p1, uint8_t(position.p2 + 1) };
                    oldposition = position;
                    position = nextPos;
                    return true;
                }
                else
                {
                    direction = (direction + 1) % direction::DIRECTIONS_TOTAL;
                    counter++;
                }
            }
            else
            {
                direction = (direction + 1) % direction::DIRECTIONS_TOTAL;
                counter++;
            }
        }
        else if (direction == direction::LEFT)
        {
            if (position.p2 > 0)
            {
                if (field[position.p1][position.p2 - 1].obj == cellObjects::Empty)
                {
                    nextPos = { position.p1, uint8_t(position.p2 - 1) };
                    oldposition = position;
                    position = nextPos;
                    return true;
                }
                else
                {
                    direction = (direction + 1) % direction::DIRECTIONS_TOTAL;
                    counter++;
                }
            }
            else
            {
                direction = (direction + 1) % direction::DIRECTIONS_TOTAL;
                counter++;
            }
        }
        else if (direction == direction::DOWN)
        {
            if (position.p2 < config::cellsHCount - 1)
            {
                if (field[position.p1 + 1][position.p2].obj == cellObjects::Empty)
                {
                    nextPos = { uint8_t(position.p1 + 1), position.p2 };
                    oldposition = position;
                    position = nextPos;
                    return true;
                }
                else
                {
                    direction = (direction + 1) % direction::DIRECTIONS_TOTAL;
                    counter++;
                }
            }
            else
            {
                direction = (direction + 1) % direction::DIRECTIONS_TOTAL;
                counter++;
            }
        }
        if (counter > 4)
        {
            oldposition = position;
            position = position;
            return false;
        }
    }

    bool SetNextPosMidGameplay(std::vector<std::pair<point, int>>& way, std::vector<std::vector<cell>>& field)
    {
        for (int i = 0; i < way.size(); i++)
        {
            if (position.p1 == way[i].first.p1 && position.p2 == way[i].first.p2)
            {
                oldposition = position;
                position = way[way[i].second].first;
                return true;
            }
        }
        if (SetNextPosEalyGameplay(field))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool SetNextPosLateGameplay(std::vector<std::pair<point, int>>& way, std::vector<std::pair<point, int>>& way2, std::vector<std::vector<cell>>& field)
    {
        for (int i = 0; i < way.size(); i++)
        {
            if (position.p1 == way[i].first.p1 && position.p2 == way[i].first.p2)
            {
                oldposition = position;
                position = way[way[i].second].first;
                return true;
            }
        }
        if (SetNextPosMidGameplay(way2, field))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    point getPosition()
    {
        return position;
    }

    point getOldPposition()
    {
        return oldposition;
    }
};

#pragma once
#include "Object.h"
class TankClass :
    public Object
{
private:
    point position;
    point oldposition;
public:
    TankClass(point pos)
    {
        this->position = pos;
        this->oldposition = pos;
    }
    ~TankClass()
    {
    }
    bool SetNextPosEalyGameplay(std::vector<std::vector<cell>>& field)
    {
        srand(time(0));
        uint8_t counter = 0;
        point nextPos;
        uint8_t direction = rand() % direction::nomberOfDirections;
        if (direction == direction::up)
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
                    direction = (direction + 1) % direction::nomberOfDirections;
                    counter++;
                }
            }
            else
            {
                direction = (direction + 1) % direction::nomberOfDirections;
                counter++;
            }
        }
        else if (direction == direction::right)
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
                    direction = (direction + 1) % direction::nomberOfDirections;
                    counter++;
                }
            }
            else
            {
                direction = (direction + 1) % direction::nomberOfDirections;
                counter++;
            }
        }
        else if (direction == direction::left)
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
                    direction = (direction + 1) % direction::nomberOfDirections;
                    counter++;
                }
            }
            else
            {
                direction = (direction + 1) % direction::nomberOfDirections;
                counter++;
            }
        }
        else if (direction == direction::down)
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
                    direction = (direction + 1) % direction::nomberOfDirections;
                    counter++;
                }
            }
            else
            {
                direction = (direction + 1) % direction::nomberOfDirections;
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


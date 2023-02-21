#pragma once

#include"BotLT.h"
#include"botTT.h"

class TanksActions
{
private:
    enum gameStage
    {
        ealy,
        mid,
        late
    };
    std::vector<Tanks*> tanks;
    std::vector<std::pair<point, int>> wayToPlayer;
    std::vector<std::pair<point, int>> wayToBase;
public:
    TanksActions(point pos)
    {
    }
    std::vector<point> checkCell(std::vector<std::vector<std::pair<cell, bool>>> field, point pos)
    {
        std::vector<point> temp;
        if (pos.p1 > 0)
        {
            if (field[pos.p1 - 1ll][pos.p2].second == false)
            {
                if (field[pos.p1 - 1ll][pos.p2].first.obj != cellObjects::Wall && field[pos.p1 - 1][pos.p2].first.obj != cellObjects::HardWall)
                {
                    point tempPos = { pos.p1 - 1, pos.p2 };
                    temp.push_back(tempPos);
                }
            }
        }
        if (pos.p1 < field.size() - 1)
        {
            if (field[pos.p1 + 1ll][pos.p2].second == false)
            {
                if (field[pos.p1 + 1][pos.p2].first.obj != cellObjects::Wall && field[pos.p1 + 1][pos.p2].first.obj != cellObjects::HardWall)
                {
                    point tempPos = { pos.p1 + 1, pos.p2 };
                    temp.push_back(tempPos);
                }
            }
        }
        if (pos.p2 > 0)
        {
            if (field[pos.p1][pos.p2 - 1].second == false)
            {
                if (field[pos.p1][pos.p2 - 1].first.obj != cellObjects::Wall && field[pos.p1][pos.p2 - 1].first.obj != cellObjects::HardWall)
                {
                    point tempPos = { pos.p1, pos.p2 - 1 };
                    temp.push_back(tempPos);
                }
            }
        }
        if (pos.p2 < field[0].size() - 1)
        {
            if (field[pos.p1][pos.p2 + 1].second == false)
            {
                if (field[pos.p1][pos.p2 + 1].first.obj != cellObjects::Wall && field[pos.p1][pos.p2 + 1].first.obj != cellObjects::HardWall)
                {
                    point tempPos = { pos.p1, pos.p2 + 1 };
                    temp.push_back(tempPos);
                }
            }
        }
        return temp;
    }
    std::vector<std::pair<point, int>> findWay(std::vector<std::vector<cell>>& fieldV, point objPos)
    {
        std::vector<std::pair<point, int>> way;
        std::vector<std::vector<std::pair<cell, bool>>> field;
        for (int i = 0; i < fieldV.size(); i++)
        {
            std::vector<std::pair<cell, bool>> tempField;
            for (int j = 0; j < fieldV[i].size(); j++)
            {
                cell cell;
                point pos = { i, j };
                cell.objHp = fieldV[i][j].objHp;
                cell.obj = fieldV[i][j].obj;
                tempField.push_back({ cell, false });
            }
            field.push_back(tempField);
            tempField.clear();
        }
        way.clear();
        std::vector<std::pair<point, short int>> nextCheck;
        std::vector<std::pair<point, short int>> nowCheck;
        field[objPos.p1][objPos.p2].second = true;
        std::vector<point> temp = checkCell(field, objPos);
        for (int i = 0; i < temp.size(); i++)
        {
            nowCheck.push_back({ temp[i], way.size() });
            field[temp[i].p1][temp[i].p2].second = true;
            way.push_back({ temp[i], 0 });
        }
        temp.clear();
        while (nowCheck.size() != 0)
        {
            for (int i = 0; i < nowCheck.size(); i++)
            {
                std::vector<point> temp = checkCell(field, nowCheck[i].first);
                for (int j = 0; j < temp.size(); j++)
                {
                    nextCheck.push_back({ temp[j], way.size() });
                    field[temp[j].p1][temp[j].p2].second = true;
                    way.push_back({ temp[j], nowCheck[i].second });
                }
                temp.clear();
            }
            nowCheck.clear();
            for (int i = 0; i < nextCheck.size(); i++)
            {
                nowCheck.push_back(nextCheck[i]);
            }
            nextCheck.clear();
        }
        field.clear();
    }
    bool setTanksPosition(std::vector<std::vector<cell>>& field, point basePos, point playerPos, gameStage stage)
    {
        bool changes = false;
        if (stage == gameStage::ealy)
        {
            for (int i = 0; i < tanks.size(); i++)
            {
                if (tanks[i]->SetNextPosEalyGameplay(field))
                {
                    changes = true;
                }
            }
        }
        else if (stage == gameStage::mid)
        {
            this->wayToPlayer = findWay(field, playerPos);
            for (int i = 0; i < tanks.size(); i++)
            {
                if (tanks[i]->SetNextPosMidGameplay(this->wayToPlayer, field))
                {
                    changes = true;
                }
            }
        }
        else if (stage == gameStage::late)
        {
            this->wayToPlayer = findWay(field, playerPos);
            this->wayToBase = findWay(field, basePos);
            for (int i = 0; i < tanks.size(); i++)
            {
                if (tanks[i]->SetNextPosLateGameplay(this->wayToBase, this->wayToPlayer, field))
                {
                    changes = true;
                }
            }
        }
        return changes;
    }
};


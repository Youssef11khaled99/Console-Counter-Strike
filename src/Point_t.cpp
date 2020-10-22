#include "Point_t.h"

using namespace std;

Point_t::Point_t(char characher, int x, int y)
{
    this->x = x;
    this->y = y;
    if (characher == 'P' || characher == '1' || characher == '2' || characher == '3')
    {
        this->baseType = ' ';
        this->isBombsite = true;
    }
    else if (characher == 'B')
    {
        this->baseType = ' ';
        this->entList.push_back(new Bomb_t(x,y));
    }
    else
    {
        this->baseType = characher;
        if (characher == 'x')
        {
            this->isWall = true;
        }
        else if (characher == '#')
        {
            this->isBridgeTunnel = true;
        }
        else if (characher == 'o')
        {
            this->isObstacle = true;
        }
    }

}

char Point_t::renderPoint()
{
    if (this->entList.empty())
    {
        return this->baseType;
    }
    else
    {
        if (std::find(this->entList.begin(), this->entList.end(), '@') != this->entList.end())
        {
            return '@';
        }
        else if (std::find(this->entList.begin(), this->entList.end(), 'C') != this->entList.end())
        {
            return 'C';
        }
        else if (std::find(this->entList.begin(), this->entList.end(), 'CT') != this->entList.end())
        {
            return 'T';
        }
        else if (std::find(this->entList.begin(), this->entList.end(), '*') != this->entList.end())
        {
            return '*';
        }
        else if (std::find(this->entList.begin(), this->entList.end(), 'B') != this->entList.end())
        {
            return 'B';
        }
        else if (std::find(this->entList.begin(), this->entList.end(), 'P') != this->entList.end())
        {
            return 'P';
        }
    }
    return this->baseType;
}

void Point_t::deleteEntFromPoint(Ent_t* entList)
{
    std::vector<int>::iterator position = std::find(this->entList.begin(), this->entList.end(), 'P');
    if (position != this->entList.end())
    {
        this->entList.erase(position);
        cout<<"Deleted Successfully"<<endl;
    }
    else
    {
        cout<<"Not Found"<<endl;
    }
}

Point_t::~Point_t()
{
    //dtor
}

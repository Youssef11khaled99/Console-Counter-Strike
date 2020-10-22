#include "Player_t.h"

Player_t::Player_t(int x, int y, bool isHuman, char team) : Ent_t(x, y)
{
    this->isHuman = isHuman;
    this->team = team;
    this->bomb = Bomb_t(0,0);
    this->lastDirection.first = x;
    this->lastDirection.second = y;

}

char Player_t::whatIam()
{
    return this->team;
}

bool Player_t::isCarryingBomb()
{
    if (this->bomb != NULL)
    {
        return true;
    }
    return false;
}

void Player_t::RIP(std::vector<Ent_t*>& p_entList)
{
    for (auto& it : p_entList) {

        // Print the values
        //cout << it << ' ';
        if (it->whatIam() == 'C' || it->whatIam() == 'T')
        {
            p_entList.erase(it);
            if (it->bomb != NULL)
            {
                this->bomb = new Bomb_t(x, y);
                this->bomb->isCarried = false;
                p_entList.push_back(bomb);
            }

        }
    }
}


Player_t::~Player_t()
{
    //dtor
}

#include "Bomb_t.h"

Bomb_t::Bomb_t(int x, int y) : Ent_t(x, y)
{
    isPlanted = false;
    isCarried = false;
    isDefused = false;
}

char Bomb_t::whatIam()
{
    return 'B';
}


Bomb_t::~Bomb_t()
{
    //dtor
}

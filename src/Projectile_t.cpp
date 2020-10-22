#include "Projectile_t.h"

Projectile_t::Projectile_t(int x, int y, char direction, Ent_t* owner) : Ent_t(x, y)
{
    this->direction = direction;
    this->owner = owner;
}

char Projectile_t::whatIam()
{
    return '*';
}

Projectile_t::~Projectile_t()
{
    //dtor
}

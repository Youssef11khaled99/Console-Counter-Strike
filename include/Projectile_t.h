#ifndef PROJECTILE_T_H
#define PROJECTILE_T_H

#include "Ent_t.h"
#include "Bomb_t.h"
#include <vector>


class Projectile_t : public Ent_t
{
    public:
        Projectile_t(int x, int y, char direction, Ent_t* owner);
        int x;
        int y;
        char whatIam();
        char direction;
        Ent_t* owner;
        ~Projectile_t();

    protected:

    private:
};

#endif // PROJECTILE_T_H

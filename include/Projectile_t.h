#ifndef PROJECTILE_T_H
#define PROJECTILE_T_H

#include "Ent_t.h"
#include "Bomb_t.h"
#include <vector>


class Projectile_t : public Ent_t
{
    public:
        Projectile_t(int x, int y);
        int x;
        int y;
        bool isHuman;
        //bomb_t bomb = nullptr;
        char lastDirection;
        bool isAlive;
        char Team;
        void RIP(std::vector<Ent_t*>& p_entList);
        ~Projectile_t();

    protected:

    private:
};

#endif // PROJECTILE_T_H

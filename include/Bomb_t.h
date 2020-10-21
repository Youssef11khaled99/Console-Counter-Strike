#ifndef BOMB_T_H
#define BOMB_T_H

#include "Ent_t.h"


class Bomb_t : public Ent_t
{
    public:
        Bomb_t(int x, int y);
        int x;
        int y;
        char whatIam();
        bool isPlanted;
        bool isCarried;
        bool isDefused;
        ~Bomb_t();

    protected:

    private:
};

#endif // BOMB_T_H

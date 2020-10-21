#ifndef PLAYER_T_H
#define PLAYER_T_H

#include "Ent_t.h"


class Player_t : public Ent_t
{
    public:
        Player_t(int x, int y);
        bool isCarryingBomb();

        ~Player_t();

    protected:

    private:
};

#endif // PLAYER_T_H

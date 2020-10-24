#ifndef PLAYER_T_H
#define PLAYER_T_H

#include "Ent_t.h"
//#include "Bomb_t.h"
#include <utility>
#include <vector>


class Player_t : public Ent_t
{
    public:
        Player_t(int x, int y, bool isHuman, char team);
        int x;
        int y;
        char whatIam();
        bool isHuman;
        //Bomb_t bomb;
        std::pair<int,int> lastDirection;
        bool isAlive;
        char team;
        bool isCarryingBomb();
        void RIP(std::vector<Ent_t*>& p_entList);

        ~Player_t();

    protected:

    private:
};

#endif // PLAYER_T_H

#ifndef AIDISPATCHER _H
#define AIDISPATCHER _H

#include<vector>
#include "Player_t.h"
#include "Level.h"
#include "BallisticDispatcher.h"

class AIDispatcher
{
    public:
        AIDispatcher (Level* &map, BallisticDispatcher* &ballistics);
        std::vector<Player_t*> botList;
        Player_t* human;
        Bomb_t* bomb;
        Level* levelref;
        BallisticDispatcher* ballref;
        void addHuman();
        void addBot();
        void addBomb();
        void printStatus();
        void checkForNewDead();
        void updateAll();

        ~AIDispatcher ();

    protected:

    private:
};

#endif // AIDISPATCHER _H

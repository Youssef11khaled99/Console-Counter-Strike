#ifndef LEVEL_H
#define LEVEL_H

#include "Point_t.h"
#include "CharMap.h"

class Level
{
    public:
        Level(CharMap*&);
        Point_t*** pointArray;
        int height;
        int width;
        CharMap* mapref;
        int roundTimer;
        int bombTimer;
        bool bombPlanted;
        int Talive;
        int Calive;
        int endCondition;
        /*   0: Not Over
             1: Bomb Defused, CT wins
             2: Bomb Exploded, T wins
             3: CT dead, T wins
             4: T dead and bomb isn't planted, CT wins
             5: Time is Up and Bomb isn't planted, CT wins.
        */
        void renderLevel();
        void clearScreen();
        int openNteamSelect();
        std::pair<int, int> mapSearch();
        void secondTick();
        void bombTick();
        bool checkRoundStatus();

        ~Level();

    protected:

    private:
};

#endif // LEVEL_H

#ifndef MOVEMENTDISPATCHER _H
#define MOVEMENTDISPATCHER _H

#include "Level.h"
#include "Player_t.h"
#include "BallisticDispatcher.h"

class MovementDispatcher
{
    public:
        MovementDispatcher ();
        static char readkeyinput();
        static void makeMove(Level* lvl, Player_t* p, char direction, BallisticDispatcher* ball);
        static void postMovemenetChecks(Level *lvl, Player_t *p);

        ~MovementDispatcher ();

    protected:

    private:
};

#endif // MOVEMENTDISPATCHER _H

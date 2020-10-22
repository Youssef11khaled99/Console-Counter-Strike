#include "MovementDispatcher.h"

MovementDispatcher ::MovementDispatcher ()
{
    //ctor
}

void MovementDispatcher ::postMovemenetChecks(Level *lvl, Player_t *p)
{
    if(p->isCarryingBomb() && to->isBombsite){
        //Plant Bomb:
        p->bomb->isPlanted = true;
        //we planted it
        p->bomb->isCarried = false;
        //therefore we are not holding it.
        p->bomb->setCoordinates(to->x, to->y);
        //update where bomb was planted
        to->entList.push_back(p->bomb);
        //save bomb to point's entList so
        //it shows in map
        p->bomb = NULL;
        //cut off link to bomb since we aren't holding it.
        //Activate Timer
        lvl->bombPlanted = true;
        //Update Game that bomb
        //is planted so tick starts!
        printw("Bomb Has Been Planted!");
        getch();
        //Just to pause execution to see if it works
    }
}

MovementDispatcher ::~MovementDispatcher ()
{
    //dtor
}

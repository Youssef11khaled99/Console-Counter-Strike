#ifndef BALLISTICDISPATCHER_H
#define BALLISTICDISPATCHER_H

#include "Projectile_t.h"
#include "Level.h"

class BallisticDispatcher
{
    public:
        BallisticDispatcher (Level*& map);
        std::vector<Projectile_t*> projList;
        Level* levelref;
        void addProjectile(Projectile_t* proj);
        void updateAll();
        ~BallisticDispatcher ();

    protected:

    private:
};

#endif // BALLISTICDISPATCHER_H

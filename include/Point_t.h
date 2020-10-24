#ifndef POINT_T_H
#define POINT_T_H

#include <vector>
#include <algorithm>
#include <iostream>
#include "Ent_t.h"
#include "Bomb_t.h"

using namespace std;

class Point_t
{
    public:
        Point_t();
        Point_t(char characher, int x, int y);
        bool isBombsite;
        bool isObstacle;
        bool isWall;
        bool isBridgeTunnel;
        char baseType;
        int x;
        int y;
        //int id;
        vector<Ent_t*>entList;
        char renderPoint();
        void deleteEntFromPoint(Ent_t* e);
        ~Point_t();
};

#endif // POINT_T_H

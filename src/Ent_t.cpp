#include "Ent_t.h"

using namespace std;

Ent_t::Ent_t(int x, int y)
{
    this->x = x;
    this->y = y;
    this->creationTime = time(0);
}

char Ent_t::whatIam()
{
    return 'E';
}

void Ent_t::setCoordinates(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Ent_t::print()
{
    cout<<"ENT_T Details:"<<endl;
    cout<<"Location==> X: "<<this->x<<"--Y: "<<this->y<<endl;
    cout<<"Creation time: "<<this->creationTime<<endl;
}

Ent_t::~Ent_t()
{
    //dtor
}

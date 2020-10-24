#include "Level.h"

Level::Level(CharMap *&originalMap)
{
    this->height = originalMap->height;
    this->width = originalMap->width;
    this->mapref = originalMap;
    this->roundTimer = 300;
    this->bombTimer = 30;
    this->Talive = 5;
    this->Calive = 5;
    this->bombPlanted = false;
    this->endCondition = 0;
    this->pointArray = new Point_t*[this->height];

    for (int i = 0; i < this->height; i++)
    {
        this->pointArray[i] = new Point_t[this->width];
    }
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            this->pointArray[i][j] = new Point_t(originalMap->map[i][j], i, j);
        }
    }

}

void Level::renderLevel()
{
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            this->pointArray[i][j]->renderPoint();
        }
    }
}

void Level::clearScreen()
{
    cout<<"Time left: "<<this->roundTimer<<endl;
    if (this->bombPlanted)
    {
        cout<<"Bomb state: Planted"<<endl;
        cout<<"Bomb timer: "<<this->bombTimer<<endl;
    }
    else
    {
        cout<<"Bomb state: Not Planted"<<endl;
    }
    cout<<"Number of current T team: "<<this->Talive<<endl;
    cout<<"Number of current C team: "<<this->Calive<<endl;

}

int Level::openNteamSelect()
{
    cout<<"Select team to play with { Terrorist (attackers) || Counter Terrorist (attackers) }"<<endl;
    cout<<"Enter A for 'T' Team OR B for 'C' Team"<<endl;
    char selectedTeam = 'Z';
    Player_t humanPlayer;
    while (selectedTeam != 'A' || selectedTeam != 'a' || selectedTeam != 'B' || selectedTeam != 'b')
    {
        cin>>selectedTeam;
        if (selectedTeam == 'A' || selectedTeam == 'a')
        {
            humanPlayer = new Player_t(0,0,true,'T');
        }
        else if (selectedTeam == 'B' || selectedTeam == 'B')
        {
            humanPlayer = new Player_t(0,0,true,'C');
        }
        else
        {
            cout<<"Please enter valid input"<<endl;
        }
    }

    this->renderLevel();
}

std::pair<int, int> Level::mapSearch()
{

}

void Level::secondTick()
{
    this->roundTimer--;
}

void Level::bombTick()
{
    this->bombTimer--;
}

bool Level::checkRoundStatus()
{
    string status = "";
    if (this->bombTimer == 0)
    {
        status += "Bomb Exploded\n";
    }
    if (this->roundTimer == 0)
    {
        status += "Time is up Game Over\n";
    }
    if (this->Calive == 0)
    {
        status += "C Team is all Dead Game Over\n";
    }
    if (this->Talive == 0)
    {
        status += "T Team is all Dead Game Over\n";
    }
    if (status != "")
    {
        cout<<status<<endl;
        return false;
    }
    return true;
}

Level::~Level()
{
    for (int i = 0; i < this->height; i++)
        delete[] this->pointArray[i];

    delete[] this->pointArray;
}

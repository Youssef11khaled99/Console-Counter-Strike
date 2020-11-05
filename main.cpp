// //Compile as: g++ ast12.cpp -lncurses

#include<iostream>    //cin/cout NOT USED. DO NOT ENABLE!
#include<fstream>       //File Streams
#include<ncurses.h>     //N Curses Library
#include<stdlib.h>      //srand
#include<time.h>        //time
#include<vector>
#include <ctime>
//#include<windows.h>
#include <unistd.h>
#include <term.h>
#include <bits/stdc++.h>


using namespace std;

void initCurses();
void endCurses();
/******************************/
class CharMap {
  public:
    CharMap(char *arg);
    CharMap(char** c, string m, int w, int h) :
        map(c), mapName(m), width(w), height(h){}
    ~CharMap();
    void printCharMap();
    char ** map;
    string mapName;
    int width;
    int height;
};
/******************************/
class Ent_t
{
    public:
        Ent_t(int x, int y);
        int x;
        int y;
        ~Ent_t();
        virtual char whatIam();
        void setCoordinates(int x,int y);
        //int idSystem;
        time_t creationTime; // should be of type time
        void print();

    protected:

    private:
};
/******************************/
class Bomb_t : public Ent_t
{
    public:
        Bomb_t();
        Bomb_t(int x, int y);
        int x;
        int y;
        char whatIam();
        bool isPlanted;
        bool isCarried;
        bool isDefused;
        ~Bomb_t();

    protected:

    private:
};
/******************************/
class Point_t
{
    public:
        Point_t();
        Point_t(int x, int y);
        Point_t(char character, int x, int y);
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
/******************************/
class Player_t : public Ent_t
{
    public:
        Player_t(int x, int y, bool isHuman, char team);
        int x;
        int y;
        char whatIam();
        bool isHuman;
        Bomb_t *bomb;
        char lastDirection;
        bool isAlive;
        char team;
        bool isCarryingBomb();
        void RIP(vector<Ent_t*>& p_entList, Ent_t* owner);

        ~Player_t();

    protected:

    private:
};

/******************************/
class Level
{
    public:
        Level(CharMap*&);
        Point_t** pointArray;
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
        Player_t* openNteamSelect();
        pair<int, int> mapSearch();
        void secondTick();
        void bombTick();
        int checkRoundStatus();

        ~Level();

    protected:

    private:
};
/******************************/
class Projectile_t : public Ent_t
{
    public:
        Projectile_t(int x, int y, char direction, Ent_t* owner);
        int x;
        int y;
        char whatIam();
        char direction;
        Ent_t* owner;
        ~Projectile_t();

    protected:

    private:
};
/******************************/
class BallisticDispatcher
{
    public:
        BallisticDispatcher (Level*& map);
        vector<Projectile_t*> projList;
        Level* levelref;
        void addProjectile(Projectile_t* proj);
        void updateAll();
        void deleteProj(int x, int y, Projectile_t* currentProj, int index);
        ~BallisticDispatcher ();

    protected:

    private:
};
/******************************/
class MovementDispatcher
{
    public:
        MovementDispatcher();
        static char readkeyinput();
        static bool makeMove(Level* lvl, Player_t* p, char direction, BallisticDispatcher* ball);
        static void postMovemenetChecks(Level *lvl, Player_t *p);

        ~MovementDispatcher ();

    protected:

    private:
};
/******************************/
class BFS_Shortest_Path {
    public:
        BFS_Shortest_Path ();
        /*
            1: for BombSite
            2: for Bomb
            3: for Player who carry the bomb
        */
        vector <pair<int,int>> BFS_Bomb_pSite(Level* lvl, Player_t* player, int Target, int RNG);
        void ViewFinding(Level* lvl, Player_t* player, BallisticDispatcher* ball);
        ~BFS_Shortest_Path ();

    protected:

    private:
};
/******************************/
class AIDispatcher
{
    public:
        AIDispatcher (Level* &map, BallisticDispatcher* &ballistics);
        int *counter;
        int delayCounter;
        vector< vector<pair<int,int>> > resVector;
        vector<Player_t*> botList;
        Player_t* human;
        Bomb_t* bomb;
        Level* levelref;
        BFS_Shortest_Path bfs;
        BallisticDispatcher* ballref;
        void addHuman(Player_t* humanPlayer);
        void addBot(int x, int y, char team);
        Bomb_t* addBomb(int x, int y);
        void printStatus();
        void checkForNewDead();
        void updateAll();

        ~AIDispatcher ();

    protected:

    private:
};
/******************************/

/******************************/

int main(int argc, char **argv)
{
    srand(time(NULL));
    //Comment out to always have the same RNG for debugging
    CharMap *map = (argc == 2) ? new CharMap(argv[1]) : NULL;
    //Read in input file
    if(map == NULL){printf("Invalid Map File\n"); return 1;}
    //close if no file given
    initCurses(); // Curses Initialisations
    //map->printCharMap();
    Level* dust2 = new Level(map);
    Player_t* player1 = dust2->openNteamSelect();

    //Add Human Player
    BallisticDispatcher* ballistics = new BallisticDispatcher(dust2); //handles ballistics for the
    // //game. It's cleaner if it is not part of level
    // //Next we will create the AI Dispatcher that will handle the Artificial Intelligence (Skynet)
    AIDispatcher* AI = new AIDispatcher(dust2, ballistics);
    AI->addHuman(player1);
    printw("BotList: %d\n",AI->botList.size());
    dust2->clearScreen();
    dust2->renderLevel();
    getch();
    clear();

    // //This also adds all players
    // //(human/bots) to AI so it can manage the pathfinding
    char ch;
    while((ch = MovementDispatcher::readkeyinput()) != 'q')
    {
        clear();
        //Super important to not mess up
        //parenthesis here else major fail.
        //This next line is the one we'd need to do asynchronous if we wanted to go that route
        if (player1->isAlive == true)
        {
            MovementDispatcher::makeMove(dust2, player1, ch, ballistics);
        }

        //reads user input, we need
        //to also pass ballistic incase projectile is shot
        AI->updateAll();
        //AIDispatcher; have the AIs move and do what they have to do to(get bomb, //defuse, kill enemies, teamkill, be toxic, etc)
        ballistics->updateAll();
        //BallisticDispatcher. Handle any ballistics
        dust2->secondTick();
        if (dust2->bombPlanted == true) dust2->bombTick();
        dust2->clearScreen();
        //Clean up before we re-render
        dust2->renderLevel();
        printw("Status: %d", dust2->checkRoundStatus());
        
        //re-render
        //Check Win Condition here (Time is out or Bomb has been defused etc etc)
        if(dust2->checkRoundStatus() != 0){break;}
        
    }

    clear();
    if (dust2->checkRoundStatus() == 1) printw("1: Bomb Defused, CT wins\n\n");
    if (dust2->checkRoundStatus() == 2) printw("2: Bomb Exploded, T wins\n\n");
    if (dust2->checkRoundStatus() == 3) printw("3: CT dead, T wins\n\n");
    if (dust2->checkRoundStatus() == 4) printw("4: T dead and bomb isn't planted, CT wins\n\n");
    if (dust2->checkRoundStatus() == 5) printw("5: Time is Up and Bomb isn't planted, CT wins\n\n");
    printw("----------------------------- GAME OVER ---------------------------------");
    delete map;
    map = NULL;
    delete dust2;
    dust2 = NULL;
    delete ballistics;
    ballistics = NULL;
    //gotta hide the evidence lol
    delete AI;
    AI = NULL;
    //we gotta delete it else it will grow into Skynet,then it's really gg D;
    //Don't delete player1 here, just handle that in the level
    printw("\ngg ez\n");
    endCurses();
    //END CURSES  
    return 0;
}

void initCurses(){
    // Curses Initialisations
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	printw("Welcome - Press Q to Exit\n");
}
void endCurses(){
	refresh();
	getch(); //Make user press any key to close
	endwin();
}

/********************************************************************/
CharMap::CharMap(char *arg){
    char temp;
    ifstream fin(arg);
    fin >> mapName;
    fin >> height;
    fin >> temp;
    fin >> width;
    map = new char*[height]; //Allocate our 2D array
    for(int i=0; i<height; i++){
        map[i] = new char[width];
        for(int j=0; j<width; j++) //Read into our array while we're at it!
            fin >> (map[i][j]) >> noskipws; //dont skip whitespace
        fin >> skipws; //skip it again just so we skip linefeed
    }
    //for(int i=0; i<height; i++){ //Uncomment if you have issues reading
    //    for(int j=0; j<width; j++) printf("%c", map[i][j]); printf("\n");};
}

void CharMap::printCharMap(){ //call only after curses is initialized!
   printw("Read Map: '%s' with dimensions %dx%d!\n",
           mapName.c_str(), height, width);
   //Note the c_str is required for C++ Strings to print with printw
   for(int i=0; i<height; i++){
       for(int j=0; j<width; j++)
           printw("%c", map[i][j]);
       printw("\n");
   }
}

CharMap::~CharMap(){
    if(map == NULL) return;
    for(int i=0; i<height; i++)
        delete [] map[i];
    delete [] map;
}
/********************************************************************/
Ent_t::Ent_t(int xx, int yy)
{
    this->x = xx;
    this->y = yy;
    this->creationTime = time(0);
}

char Ent_t::whatIam()
{
    return 'E';
}

void Ent_t::setCoordinates(int xx, int yy)
{
    this->x = xx;
    this->y = yy;
}

void Ent_t::print()
{
    printw("ENT_T Details: \n");
    printw("Location==> X: %d , Y: %d \n",this->x,this->y);
    //printw("Creation time: \n",this->creationTime);
}

Ent_t::~Ent_t()
{
    //dtor
}
/********************************************************************/
Bomb_t::Bomb_t() : Ent_t(x,y)
{

}

Bomb_t::Bomb_t(int x, int y) : Ent_t(x, y)
{
    isPlanted = false;
    isCarried = false;
    isDefused = false;
}

char Bomb_t::whatIam()
{
    return 'B';
}

Bomb_t::~Bomb_t()
{
    //dtor
}
/********************************************************************/
Level::Level(CharMap *&originalMap)
{
    this->height = originalMap->height;
    this->width = originalMap->width;
    this->mapref = originalMap;
    this->roundTimer = 300;
    this->bombTimer = 30;
    this->Talive = 1;
    this->Calive = 1;
    this->bombPlanted = false;
    this->endCondition = 0;
    // dynamically create array of pointers of size height
    Point_t** tmp = new Point_t*[height];
	// dynamically allocate memory of size width for each row
    for (int i = 0; i < height; i++)
        tmp[i] = new Point_t[width];

//    pointArray = new Point_t*[this->height];
//
//    for (int i = 0; i < this->height; i++)
//    {
//        this->pointArray[i] = new Point_t[this->width];
//    }
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            Point_t pTmp = Point_t(originalMap->map[i][j], i, j);
            tmp[i][j] = pTmp;
        }
    }
    pointArray = tmp;

}

void Level::renderLevel()
{

    printw("Read Map: '%s' with dimensions %dx%d!\n",
    mapref->mapName.c_str(), height, width);

    for(int i=0; i<height; i++)
    {
       for(int j=0; j<width; j++)
       {
           printw("%c", pointArray[i][j].renderPoint());
       }
       printw("\n");
   }
}

void Level::clearScreen()
{
    printw("Time left: %d\n",this->roundTimer);
    if (this->bombPlanted)
    {
        printw("Bomb state: Planted\n");
        printw("Bomb timer: %d\n",this->bombTimer);
    }
    else
    {
        printw("Bomb state: Not Planted\n");
    }
    printw("Number of current T team: %d\n",this->Talive);
    printw("Number of current C team: %d\n",this->Calive);

}

Player_t* Level::openNteamSelect()
{
    printw("Select team to play with { Terrorist (Attackers) || Counter Terrorist (Defenders) }\n");
    printw("Enter A for 'T' Team OR B for 'C' Team OR I if you don't want to play\n");
    char selectedTeam;
    Player_t *player;
    
    while (selectedTeam != 'q')
    {
        selectedTeam = getch();
        printw("Team: %c \n",selectedTeam);
        if (selectedTeam == 'a' || selectedTeam == 'A')
        {
            printw("Okay you select T Attackers Team\n");
            player = new Player_t(4,7,true,'T');
            break;
        }
        else if (selectedTeam == 'b' || selectedTeam == 'B')
        {
            printw("Okay you select C Defenders Team\n");
            player = new Player_t(4,7,true,'C');
            break;
        }
        else if (selectedTeam == 'i' || selectedTeam == 'I') 
        {
            printw("Okay don't select any team, then you will watch bots playing\n");
            player = new Player_t(4,7,false,'C');
            break;
        }
        else
        {
            printw("Please enter valid input\n");
        }
    }    
    // this->renderLevel();
    return player; // I don't know yet what I should return
}

pair<int, int> Level::mapSearch()
{
    // Just for test
    pair<int, int> test;
    test.first = 1;
    test.second = 2;
    return test;
}

void Level::secondTick()
{
    --this->roundTimer;
}

void Level::bombTick()
{
    --this->bombTimer;
}

int Level::checkRoundStatus()
{
    /*   0: Not Over
             1: Bomb Defused, CT wins
             2: Bomb Exploded, T wins
             3: CT dead, T wins
             4: T dead and bomb isn't planted, CT wins
             5: Time is Up and Bomb isn't planted, CT wins.
    */
    // if (this-> == 0) Bomb defused
    // {
    //     endCondition = 2
    // }
    if (this->bombTimer == 0)
    {
        endCondition = 2;
    }
    if (this->Calive == 0)
    {
        endCondition = 3;
    }
    if (this->Talive == 0)
    {
        endCondition = 4;
    }
    if (this->roundTimer == 0)
    {
        endCondition = 5;
    }
    return endCondition;
}

Level::~Level()
{
    for (int i = 0; i < this->height; i++)
        delete[] this->pointArray[i];

    delete[] this->pointArray;
}
/********************************************************************/
Player_t::Player_t(int xx, int yy, bool isHuman, char team) : Ent_t(xx, yy)
{
    this->isHuman = isHuman;
    this->team = team;
    this->bomb = NULL;
    this->isAlive = true;
    this-> x = xx;
    this-> y = yy;
    this->lastDirection = 'l';

}

char Player_t::whatIam()
{
    if (isHuman)
    {
        return '@';
    }
    return this->team;
}

bool Player_t::isCarryingBomb()
{
    if (this->bomb == NULL)
    {
        return false;
    }
    return true;
}

void Player_t::RIP(vector<Ent_t*>& p_entList, Ent_t* owner)
{
    for (int i = 0; i < p_entList.size(); i++)
    {
        if (
            (p_entList[i]->whatIam() == '@' ||
            p_entList[i]->whatIam() == 'C' ||
            p_entList[i]->whatIam() == 'T')
            &&
            p_entList[i] != owner )
        {
            printw("RIIIIP\n");
            dynamic_cast<Player_t*>(p_entList[i])->isAlive = false;
            p_entList.erase(p_entList.begin() + i);
            if (dynamic_cast<Player_t*>(p_entList[i])->isCarryingBomb())
            {
                Bomb_t *bomb = new Bomb_t(x, y);
                bomb->isCarried = false;
                p_entList.push_back(bomb);
            }
            i--;
        }
    }
}

Player_t::~Player_t()
{
    //dtor
}
/********************************************************************/
Point_t::Point_t()
{
    this->x = x;
    this->y = y;
    isBombsite = false;
    isObstacle = false;
    isWall = false;
    isBridgeTunnel = false;
}

Point_t::Point_t(int x, int y)
{
    this->x = x;
    this->y = y;
    isBombsite = false;
    isObstacle = false;
    isWall = false;
    isBridgeTunnel = false;
}

Point_t::Point_t(char character, int x, int y)
{
    this->x = x;
    this->y = y;
    isBombsite = false;
    isObstacle = false;
    isWall = false;
    isBridgeTunnel = false;
    if (character == 'P' || character == '1' || character == '2' || character == '3')
    {
        this->baseType = character;
        this->isBombsite = true;
    }
    else if (character == 'B')
    {
        this->baseType = ' ';
        this->entList.push_back(new Bomb_t(x,y));
    }
    else if (character == 'C')
    {
        this->baseType = 'C';
    }
    else if (character == 'T')
    {
        this->baseType = 'T';
    }
    else
    {
        this->baseType = character;
        if (character == 'x')
        {
            this->isWall = true;
        }
        else if (character == '#')
        {
            this->isBridgeTunnel = true;
        }
        else if (character == 'o')
        {
            this->isObstacle = true;
        }
    }

}

char Point_t::renderPoint()
{
    if (this->entList.size() == 0)
    {
        return this->baseType;
    }
    else
    {
        // ana 3awz a3ml sort 34an m4 2wl ent y5odha
        char res;
        for (int i = 0; i < this->entList.size(); i++)
        {
            if (this->entList[i]->whatIam() == '@') res = '@';
            else if (this->entList[i]->whatIam() == 'C') res = 'C';
            else if (this->entList[i]->whatIam() == 'T') res = 'T';
            else if (this->entList[i]->whatIam() == '*') res = '*';
            else if (this->entList[i]->whatIam() == 'B') res = 'B';
            else if (this->entList[i]->whatIam() == 'P') res = 'P';
        }
        return res;
    }
    return this->baseType;
}

void Point_t::deleteEntFromPoint(Ent_t* e)
{        
    for (int i = 0; i < this->entList.size(); i++)
    {
        if (this->entList[i]->whatIam() == e->whatIam())
        {
            this->entList.erase(this->entList.begin() + i);
            return;
        }
    }
    e = NULL;
    delete e;
}

Point_t::~Point_t()
{
    //dtor
}
/********************************************************************/
Projectile_t::Projectile_t(int x, int y, char direction, Ent_t* owner) : Ent_t(x, y)
{
    this->direction = direction;
    this->owner = owner;
    this->x = x;
    this->y = y;
}

char Projectile_t::whatIam()
{
    return '*';
}

Projectile_t::~Projectile_t()
{
    //dtor
}
/********************************************************************/
BallisticDispatcher::BallisticDispatcher(Level* &map)
{
    this->levelref = map;

}

void BallisticDispatcher::addProjectile(Projectile_t* proj)
{
    projList.push_back(proj);
}

void BallisticDispatcher::updateAll()
{ 
    for (int i = 0; i < projList.size(); i++)
    {
        char proDirec = projList[i]->direction;
        int currentX = projList[i]->x;
        int currentY = projList[i]->y;

        int oldX = projList[i]->x;
        int oldY = projList[i]->y;
        Player_t *projOwner = dynamic_cast<Player_t*>(projList[i]->owner);

        if (proDirec == 'u') --currentX;//Up
        else if (proDirec == 'd') ++currentX;//Down
        else if (proDirec == 'r') ++currentY;//Right
        else if (proDirec == 'l') --currentY;//Left

        if (levelref->pointArray[currentX][currentY].isWall == true)
        {
            deleteProj(oldX, oldY, projList[i], i);
            i--;
        }
        else
        {
            if ( levelref->pointArray[currentX][currentY].entList.size() == 0 )
            {
                levelref->pointArray[oldX][oldY].deleteEntFromPoint(projList[i]);
                levelref->pointArray[currentX][currentY].entList.push_back(projList[i]);
                projList[i]->x = currentX;
                projList[i]->y = currentY;
            }
            else
            {
                for (int j = 0; j < levelref->pointArray[currentX][currentY].entList.size(); j++)
                {
                    if (levelref->pointArray[currentX][currentY].entList[j]->whatIam() == '*')
                    {
                        levelref->pointArray[oldX][oldY].deleteEntFromPoint(projList[i]);
                        // levelref->pointArray[currentX][currentY].entList.push_back(projList[i]);
                        projList[i]->x = currentX;
                        projList[i]->y = currentY;

                    }
                    else if (levelref->pointArray[currentX][currentY].entList[j]->whatIam() == '@' ||
                        levelref->pointArray[currentX][currentY].entList[j]->whatIam() == 'C' ||
                        levelref->pointArray[currentX][currentY].entList[j]->whatIam() == 'T' &&
                        levelref->pointArray[currentX][currentY].entList[j] != projOwner
                        )
                    {
                        deleteProj(oldX, oldY, projList[i], i);
                        i--;
                        Player_t* deadPlayer = dynamic_cast<Player_t*>(levelref->pointArray[currentX][currentY].entList[j]);
                        deadPlayer->RIP(levelref->pointArray[currentX][currentY].entList, projOwner);
                        getch();
                        clear();
                        printw("Printing deadPlayer Details: \n");
                        printw("isHuman: %d \n", deadPlayer->isHuman);
                        printw("isAlive: %d \n", deadPlayer->isAlive);
                        printw("team: %c \n", deadPlayer->team);
                        printw("isCarrying Bomb: %d \n", deadPlayer->isCarryingBomb());
                        
                        getch();
                        clear();
                    }
                    else 
                    {
                        levelref->pointArray[oldX][oldY].deleteEntFromPoint(projList[i]);
                        levelref->pointArray[currentX][currentY].entList.push_back(projList[i]);
                        projList[i]->x = currentX;
                        projList[i]->y = currentY;
                    }
                }
                
            }
        }
    }
}

void BallisticDispatcher::deleteProj(int x, int y, Projectile_t* currentProj, int index)
{
    levelref->pointArray[x][y].deleteEntFromPoint(currentProj);
    projList.erase(projList.begin() + index);
    printw("Deleting Proj\n");
    currentProj = NULL;
    delete currentProj;
}

BallisticDispatcher::~BallisticDispatcher()
{
    //dtor
}
/********************************************************************/
MovementDispatcher ::MovementDispatcher ()
{
    //ctor
}

char MovementDispatcher::readkeyinput()
{
    char moveChar = getch();
    if (moveChar == 'q' || moveChar == 'Q') return 'q';
    if (moveChar == 'W' || moveChar == 'w' || moveChar == KEY_UP) return 'u';
    if (moveChar == 'S' || moveChar == 's' || moveChar == KEY_DOWN) return 'd';
    if (moveChar == 'D' || moveChar == 'd' || moveChar == KEY_RIGHT) return 'r';
    if (moveChar == 'A' || moveChar == 'a' || moveChar == KEY_LEFT) return 'l';
    if (moveChar == ' ') return ' ';
    if (moveChar == 'I' || moveChar == 'i') return 'i';
    else
    {
        readkeyinput();
    }
    return 'i';

}

bool MovementDispatcher::makeMove(Level* lvl, Player_t* p, char direction, BallisticDispatcher* ball)
{
    int currentX = p->x;
    int currentY = p->y;
    int oldX = p->x;
    int oldY = p->y;
    bool status;

    printw("You make a %c Move\n", direction);
    if (direction == 'u') --currentX;//Up
    else if (direction == 'd') ++currentX;//Down
    else if (direction == 'r') ++currentY;//Right
    else if (direction == 'l') --currentY;//Left
    else if (direction == ' ')//Shoot Proj.
    {
        // printw("Shooting Proj .....\n");
        Projectile_t *proj = new Projectile_t(currentX, currentY, p->lastDirection, p);
        ball->addProjectile(proj);
        return true;
    }
    else if (direction == 'i') return true; // idle

    
    if (lvl->pointArray[currentX][currentY].baseType == ' ' || 
        lvl->pointArray[currentX][currentY].baseType == 'T' || 
        lvl->pointArray[currentX][currentY].baseType == 'C' ||
        lvl->pointArray[currentX][currentY].baseType == '1' || 
        lvl->pointArray[currentX][currentY].baseType == '2' || 
        lvl->pointArray[currentX][currentY].baseType == 'P')
    {
        lvl->pointArray[oldX][oldY].deleteEntFromPoint(p);
        // p->setCoordinates(currentX, currentY);
        p->x = currentX;
        p->y = currentY;
        lvl->pointArray[currentX][currentY].entList.push_back(p);
        status = true;
    }
    // Moving over BridgeTunnel
    else if (lvl->pointArray[currentX][currentY].isBridgeTunnel == true)
    {
        if(
            ( p->lastDirection == 'u' && (direction == 'u' || direction == 'd')) ||
            ( p->lastDirection == 'd' && (direction == 'u' || direction == 'd')) ||
            ( p->lastDirection == 'r' && (direction == 'r' || direction == 'l')) ||
            ( p->lastDirection == 'l' && (direction == 'r' || direction == 'l')) )
        {
            printw("lastDirection: %c ---- currentDirection: %c", p->lastDirection, direction);
            printw("Moving in Tunnel. . . .\n\n");
            lvl->pointArray[oldX][oldY].deleteEntFromPoint(p);
            p->x = currentX;
            p->y = currentY;
            lvl->pointArray[currentX][currentY].entList.push_back(p);
            status = true;
            // p->setCoordinates(currentX, currentY);
        }
        else 
        {
            printw("Can't move >>>\n");
            status =false;
        }
            
    }
    else {
        printw("Can't move >>>\n");
        status =false;
    }
    
    p->lastDirection = direction;
    postMovemenetChecks(lvl, p);
    return status;
}

void MovementDispatcher::postMovemenetChecks(Level *lvl, Player_t *p)
{
    Point_t currentPoint = lvl->pointArray[p->x][p->y];
    if (p->team == 'T')
    {
        for (int i = 0; i < lvl->pointArray[p->x][p->y].entList.size(); i++)
        {
            if (lvl->pointArray[p->x][p->y].entList[i]->whatIam() == 'B' && lvl->pointArray[p->x][p->y].isBombsite == false)
            {
                p->bomb = new Bomb_t(p->x, p->y);
                p->bomb->isCarried = true;
                Ent_t *tmp = new Bomb_t(p->x,p->y);
                lvl->pointArray[p->x][p->y].deleteEntFromPoint(tmp);
            }
        }
        if(p->isCarryingBomb() && lvl->pointArray[p->x][p->y].isBombsite && lvl->bombPlanted == false){
            //Plant Bomb:
            p->bomb->isPlanted = true;
            //we planted it
            p->bomb->isCarried = false;
            //therefore we are not holding it.
            //p->bomb->setCoordinates(currentPoint.x, currentPoint.y);
            p->bomb->x = lvl->pointArray[p->x][p->y].x;
            p->bomb->y = lvl->pointArray[p->x][p->y].y;
            //update where bomb was planted
            lvl->pointArray[p->x][p->y].entList.push_back(p->bomb);
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
    if (p->team == 'C')
    {
        for (int i = 0; i < lvl->pointArray[p->x][p->y].entList.size(); i++)
        {
            if (lvl->pointArray[p->x][p->y].entList[i]->whatIam() == 'B')
            {
                //Defused Bomb:
                dynamic_cast<Bomb_t*>(lvl->pointArray[p->x][p->y].entList[i])->isDefused = true;

                lvl->endCondition = 1;

                printw("Bomb Has Been Defused!");
                getch();
                //Just to pause execution to see if it works
            }
        }
    }

}

MovementDispatcher ::~MovementDispatcher ()
{
    //dtor
}
/********************************************************************/
BFS_Shortest_Path::BFS_Shortest_Path()
{


}

vector <pair<int,int>> BFS_Shortest_Path::BFS_Bomb_pSite(Level* lvl, Player_t* player, int Target, int RNG)
{
    /*
        1: for BombSite
        2: for Bomb
        3: for Player who carry the bomb
    */

    //parent , x ,y
    queue <pair<pair<int,int> ,pair<int,int> >> q;
    pair <int,int> pos = {player->x,player->y};
    q.push({ {-1,-1} , {pos.first,pos.second} } );
    // x,y , parent
    map<pair<int,int>,pair<int,int> > visited;
    visited.insert({{pos.first,pos.second},{-1,-1}});
    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};
    int destX;
    int destY;
    while(q.size()){
        pair<pair<int,int> ,pair<int,int> > curr = q.front();
        int x = curr.second.first;
        int y = curr.second.second;
        int px = curr.first.first;
        int py = curr.first.second;
        q.pop();
        if (Target == 1)
        {
            if (RNG == 1 && lvl->pointArray[x][y].baseType == '2')
            {
                printw("Going to bombsite 1\n");
                destX = x;
                destY = y;
                break;
            }
            else if (RNG == 0 && lvl->pointArray[x][y].baseType == '1')
            {
                printw("Skipping the first bombSite\n");
                destX = x;
                destY = y;
                break;
            }
        }
        else if (Target == 2)
        {
            for (int i = 0; i < lvl->pointArray[x][y].entList.size(); ++i)
            {
                if (lvl->pointArray[x][y].entList[i]->whatIam() == 'B')
                {
                    destX = x;
                    destY = y;
                    break;
                }
            }
        }
        else if (Target == 3)
        {
            for (int i = 0; i < lvl->pointArray[x][y].entList.size(); i++)
            {
                if (lvl->pointArray[x][y].entList[i]->whatIam() == 'T' &&
                    dynamic_cast<Player_t*>(lvl->pointArray[x][y].entList[i])->isCarryingBomb() == true)
                {
                    destX = x;
                    destY = y;
                    break;
                }
            }
        }
        
        /*
            0: ++currentX;//Down
            1: --currentX;//Up
            2: ++currentY;//Right
            3: --currentY;//Left
        */
        for (int i = 0 ; i < 4 ;++i){
            int nx = x + dx[i];
            int ny = y + dy[i];
            // printw("visited: %d\n", visited.count({nx, ny}));
            if (visited.count({nx,ny}) ||
                lvl->pointArray[nx][ny].isWall == true  ||
                lvl->pointArray[nx][ny].isObstacle == true
                )
            {
                continue;
            }
            // Moving over BridgeTunnel
            if (lvl->pointArray[nx][ny].isBridgeTunnel == true)
            {
                if(
                    ( player->lastDirection == 'u' && (i == 0 || i == 1)) ||
                    ( player->lastDirection == 'd' && (i == 0 || i == 1)) ||
                    ( player->lastDirection == 'r' && (i == 2 || i == 3)) ||
                    ( player->lastDirection == 'l' && (i == 2 || i == 3)) )
                {
                    // printw("I'm going to enter the bridge\n");
                    // printw("x: %d || y: %d \n", nx,ny);
                    visited.insert({{nx,ny},{x,y}});
                    q.push({{x,y},{nx,ny}});
                } 
            }
            else 
            {
                visited.insert({{nx,ny},{x,y}});
                q.push({{x,y},{nx,ny}});
            }
            
        }
    }
    vector<pair<int,int> > v;
    while (destX != -1){
        v.push_back({destX,destY});
        auto p = visited[{destX,destY}]; 
        destX = p.first;
        destY = p.second;
    }
    reverse(v.begin(),v.end());
    return v;
}
void BFS_Shortest_Path::ViewFinding(Level* lvl, Player_t* player, BallisticDispatcher* ball)
{
    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};
    int x = player->x;
    int y = player->y;
    /*
        0: ++currentX;//Down
        1: --currentX;//Up
        2: ++currentY;//Right
        3: --currentY;//Left
    */
    for (int i = 0; i < 4; ++i)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        while (lvl->pointArray[nx][ny].isWall != true)
        {
            for (int j = 0; j < lvl->pointArray[nx][ny].entList.size(); ++j)
            {
                if (
                    ( lvl->pointArray[nx][ny].entList[j]->whatIam() == 'C' && player->team == 'T' )||
                    ( lvl->pointArray[nx][ny].entList[j]->whatIam() == 'T' && player->team == 'C' ) ||
                    ( lvl->pointArray[nx][ny].entList[j]->whatIam() == '@' && player->team != dynamic_cast<Player_t*>(lvl->pointArray[nx][ny].entList[j])->team)  
                    )
                {   
                    if 
                    (
                        i == 0 && player->lastDirection == 'd' ||
                        i == 1 && player->lastDirection == 'u' ||
                        i == 2 && player->lastDirection == 'r' ||
                        i == 3 && player->lastDirection == 'l' 
                    )   
                    {
                        printw("The enemy is in my same direction!!\n");
                        MovementDispatcher::makeMove(lvl, player,' ', ball);
                        return;
                    }
                    else if (i == 0)
                    {
                        MovementDispatcher::makeMove(lvl, player,'d', ball);
                    }
                    else if (i == 1)
                    {
                        MovementDispatcher::makeMove(lvl, player,'u', ball);
                    }
                    else if (i == 2)
                    {
                        MovementDispatcher::makeMove(lvl, player,'r', ball);
                    }
                    else if (i == 3)
                    {
                        MovementDispatcher::makeMove(lvl, player,'l', ball);
                    }
                    //MovementDispatcher::makeMove(lvl, player,' ', ball);
                    printw("Returning after changing direction!!\n");
                    return;
                }
            }
            nx += dx[i];
            ny += dy[i];
            
        }
        
    }
}
BFS_Shortest_Path::~BFS_Shortest_Path()
{

}
/********************************************************************/
AIDispatcher::AIDispatcher(Level* &map, BallisticDispatcher* &ballistics)
{
    levelref = map;
    ballref = ballistics;
    human->isAlive == false;
    // Adding all first team bots
    
    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            
            if (levelref->pointArray[i][j].baseType == 'C')
            {
                addBot(i, j, 'C');
                getch();
                clear();
                printw("adding five bots to the C Team successfully\n");
            } 
            else if (levelref->pointArray[i][j].baseType == 'T')
            {
                addBot(i, j, 'T');
                getch();
                clear();
                printw("adding five bots to the T Team successfully\n");
            } 
            // else if (levelref->pointArray[i][j].entList[k]->whatIam() == 'B') 
            // {
            //     this->bomb = addBomb(i, j);
            //     levelref->pointArray[i][j].entList.push_back(bomb);

            // }
        }
    }
    counter = new int [botList.size()];
    for (int i = 0; i < botList.size(); i++)
    {
        counter[i] = 0;
        int RNG;
        if (botList[i]->team == 'T')
        {
            RNG = rand() % 2;
            vector<pair<int,int>> tmpVector = bfs.BFS_Bomb_pSite(this->levelref, botList[i], 1, RNG);
            resVector.push_back(tmpVector);
        }
        else if (botList[i]->team == 'C')
        {
            RNG = rand() % 2;
            vector<pair<int,int>> tmpVector = bfs.BFS_Bomb_pSite(this->levelref, botList[i], 1, RNG);
            resVector.push_back(tmpVector);
        }
        // ViewFinding(); -- BFS
        // PathFinding(); -- BFS brdo
    }
} 

void AIDispatcher::addHuman(Player_t* humanPlayer)
{
    human = humanPlayer;
    for (int i = 0; i < botList.size(); i++)
    {
        if (botList[i]->team == humanPlayer->team)
        {
            Point_t* currentPoint = new Point_t();
            for (int j = 0; j < levelref->pointArray[botList[i]->x][botList[i]->y].entList.size(); j++)
            {
                if (levelref->pointArray[botList[i]->x][botList[i]->y].entList[j]->whatIam() == botList[i]->whatIam())
                {
                    levelref->pointArray[botList[i]->x][botList[i]->y].entList.erase(levelref->pointArray[botList[i]->x][botList[i]->y].entList.begin() + j);
                    break;
                }
            }
            botList.erase(botList.begin() + i);
            
            break;
        }

    }
    for (int i = 0; i < levelref->height; i++)
    {
        for (int j = 0; j < levelref->width; j++)
        {
            if (levelref->pointArray[i][j].baseType == 'C' && humanPlayer->team == 'C')
            {
                // humanPlayer->setCoordinates(i, j);
                humanPlayer-> x = i;
                humanPlayer -> y = j;

                botList.push_back(humanPlayer);
                levelref->pointArray[i][j].entList.push_back(humanPlayer);
            } 
            else if (levelref->pointArray[i][j].baseType == 'T' && humanPlayer->team == 'T')
            {
                // humanPlayer->setCoordinates(i, j);
                humanPlayer-> x = i;
                humanPlayer -> y = j;

                botList.push_back(humanPlayer);
                levelref->pointArray[i][j].entList.push_back(humanPlayer);
            } 
        }
    }
}

void AIDispatcher::addBot(int x, int y, char team)
{
    Player_t* newBot;
    // for (int i = 0; i < 5; i++)
    // {
    //     newBot = new Player_t(x, y, false, team);
    //     botList.push_back(newBot);
    //     levelref->pointArray[x][y].entList.push_back(newBot);
    // }
    newBot = new Player_t(x, y, false, team);
    botList.push_back(newBot);
    levelref->pointArray[x][y].entList.push_back(newBot);
}

// Bomb_t* AIDispatcher::addBomb(int x, int y)
// {
//     return new Bomb_t(x, y);
// }

void AIDispatcher::printStatus()
{
    printw("log messages :) ");
}

void AIDispatcher::checkForNewDead()
{
    for (int i = 0; i < botList.size(); i++)
    {
        if (botList[i]->isAlive == false && botList[i]->team == 'C')
        {
            --levelref->Calive;
            printw("number of C alive: %d\n", levelref->Calive); 
            botList[i] = NULL;
            botList.erase(botList.begin() + i);  
            i--;
        }
        else if (botList[i]->isAlive == false && botList[i]->team == 'T')
        {
            --levelref->Talive;
            printw("number of T alive: %d\n", levelref->Talive);
            botList[i] = NULL;
            botList.erase(botList.begin() + i);
            i--;
        }
    }
}

void AIDispatcher::updateAll()
{
    checkForNewDead();
    printw("Human Status: %d\n",human->isAlive);
    if (human-> isAlive == false) delayCounter--;
    for (int i = 0; i < botList.size(); i++)
    {
        if (botList[i]->isHuman == false)
        {
            // printw("Bot Team: %c\n",botList[i]->team);
            
            if (botList[i]->team == 'T')
            {
                printw("IsCarryingBomb: %d\n",botList[i]->isCarryingBomb());
                int botTarget = 1;
                
                // resVector[i] = bfs.BFS_Bomb_pSite(levelref, botList[i], 1, 1);
                // if the bomb in dropped
                if (botList[i]->isCarryingBomb() == false && levelref->bombPlanted == false)
                {
                    getch();
                    clear();
                    printw("Size before %d\n", resVector[i].size());
                    resVector[i] = bfs.BFS_Bomb_pSite(levelref, botList[i], 2, 1);
                    printw("Size After %d\n", resVector[i].size());
                    getch();
                    clear();


                    // if (delayCounter == 0 || human->isAlive == false)
                    // {
                    //     resVector[i] = bfs.BFS_Bomb_pSite(this->levelref, botList[i], botObjective);
                    // }
                    // else 
                    // {
                    //     printw("10 Ticks delay for the Human Player to pick the bomb\n");
                    // }
                    
                } 
                else {
                    printw("Im in else!!\n");

                    resVector[i] = bfs.BFS_Bomb_pSite(levelref, botList[i], 1, 1);
                    counter[i] = 0;
                }
                // If I carry the bomb
                // else if (botList[i]->isCarryingBomb() == true)
                // {
                //     printw("going to the bomb site\n");
                //     resVector[i] = bfs.BFS_Bomb_pSite(this->levelref, botList[i], 1);
                // }
                // else if (bomb->isCarried == true && botList[i]->isCarryingBomb() == false)
                // {
                //     int RND = rand() % 2; 
                //     if (RND == 1)
                //         resVector[i] = bfs.BFS_Bomb_pSite(this->levelref, botList[i], 3);
                //     else 
                //         resVector[i] = bfs.BFS_Bomb_pSite(this->levelref, botList[i], 1);
                // }
                // else if (bomb->isPlanted == true)
                // {
                //     resVector[i] = bfs.BFS_Bomb_pSite(this->levelref, botList[i], 1);
                // }
                // else
                // {
                //     resVector[i] = bfs.BFS_Bomb_pSite(this->levelref, botList[i], 1);
                // }
                
                // printw("Bot C: %d || %d\n",botList[i]->x,botList[i]->y);
                // resVector[i] = bfs.BFS_Bombsite(this->levelref, botList[i]);
                
                // printw("ENNNND\n");
            }
            // else if (botList[i]->team == 'C')
            // {
                
            // }
            // AL MO4KALA HNA ==>

            char moveDirection;
            if (counter[i] != resVector[i].size() - 1)
            {
                // printw("SIzze: %d\n", resVector[i].size());
                // printw("Counter[i]: %d\n",counter[i]);
                /*
                    0: ++currentX;//Down
                    1: --currentX;//Up
                    2: ++currentY;//Right
                    3: --currentY;//Left
                */
                if (resVector[i][counter[i]].first - resVector[i][counter[i] + 1].first > 0)
                {
                    moveDirection = 'u';
                    ++counter[i];
                    
                } 
                else if (resVector[i][counter[i]].first - resVector[i][counter[i] + 1].first < 0)
                {
                    moveDirection = 'd';
                    ++counter[i];
                } 
                else if (resVector[i][counter[i]].second - resVector[i][counter[i] + 1].second > 0)
                {
                    moveDirection = 'l';
                    ++counter[i];
                } 
                else if (resVector[i][counter[i]].second - resVector[i][counter[i] + 1].second < 0)
                {
                    moveDirection = 'r';
                    ++counter[i];
                } 
                bool canMove = MovementDispatcher::makeMove(levelref, botList[i], moveDirection,ballref);
                // printw("current Counter: %d\n", counter[i]);
                if (!canMove)
                {
                    printw("Cant move in update All\n");
                    counter[i] = 0;
                    int RNG = 1;
                    resVector[i] = bfs.BFS_Bomb_pSite(this->levelref, botList[i], 1, RNG);
                }
            }
            bfs.ViewFinding(levelref, botList[i], ballref);
        }
        
        // ViewFinding(); -- BFS
        // PathFinding(); -- BFS brdo
    }
    

}

AIDispatcher::~AIDispatcher()
{
    //dtor
}
/********************************************************************/

/********************************************************************/

/********************************************************************/
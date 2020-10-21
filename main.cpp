// //Compile as: g++ ast12.cpp -lncurses

#include<iostream>    //cin/cout NOT USED. DO NOT ENABLE!
#include<fstream>       //File Streams
#include<ncurses.h>     //N Curses Library
#include<stdlib.h>      //srand
#include<time.h>        //time
//#include<windows.h>
#include "CharMap.h"
#include "Level.h"
#include "Player_t.h"
#include "BallisticDispatcher.h"
#include "AIDispatcher.h"
#include "MovementDispatcher.h"

using namespace std;

 void initCurses();
 void endCurses();

// //Your Code Here

int main(int argc, char **argv)
{
    srand(time(NULL));
    //Comment out to always have the same RNG for debugging
    CharMap *map = (argc == 2) ? new CharMap(argv[1]) : NULL;
    //Read in input file
    if(map == NULL){printf("Invalid Map File\n"); return 1;}
    //close if no file given
    initCurses(); // Curses Initialisations
    //map->print();
    Level* dust2 = new Level(map);
    //-->//Player_t* player1 = dust2->openNteamSelect();
    //Add Human Player
    BallisticDispatcher* ballistics = new BallisticDispatcher(dust2); //handles ballistics for the
    //game. It's cleaner if it is not part of level
    //Next we will create the AI Dispatcher that will handle the Artificial Intelligence (Skynet)
    AIDispatcher* AI = new AIDispatcher(dust2, ballistics);
    //This also adds all players
    //(human/bots) to AI so it can manage the pathfinding
    //Main Loop
    char ch;
    while((ch = MovementDispatcher::readkeyinput()) != 'q')
    {
        //Super important to not mess up
        //parenthesis here else major fail.
        //This next line is the one we'd need to do asynchronous if we wanted to go that route
        //-->//MovementDispatcher::makeMove(dust2, player1, ch, ballistics);
        //reads user input, we need
        //to also pass ballistic incase projectile is shot
        AI->updateAll();
        //AIDispatcher; have the AIs move and do what they have to do to(get bomb, //defuse, kill enemies, teamkill, be toxic, etc)
        ballistics->updateAll();
        //BallisticDispatcher. Handle any ballistics
        dust2->clearScreen();
        //Clean up before we re-render
        dust2->renderLevel();
        //re-render
        //Check Win Condition here (Time is out or Bomb has been defused etc etc)
        if(dust2->checkRoundStatus() != 0){break;}
    }
     delete map;
     map = NULL;
     delete dust2, dust2 = NULL;
     delete ballistics;
     ballistics = NULL;
     //gotta hide the evidence lol
     delete AI;
     AI = NULL;
     //we gotta delete it else it will grow into Skynet,then it's really gg D;
     //Don't delete player1 here, just handle that in the level
     printw("\ngg ez\n");
     endCurses();
     //END CURSES  return 0;
}


//
//int main(){
//    cout<< "hello world";
//
//}

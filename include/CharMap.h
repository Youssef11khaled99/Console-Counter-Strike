#ifndef CHARMAP_H
#define CHARMAP_H

#include<fstream>       //File Streams
#include<ncurses.h>     //N Curses Library
#include<stdlib.h>      //srand
#include<time.h>
#include<iostream>

using namespace std;

class CharMap {
  public:
    CharMap(char *arg);
    CharMap(char** c, std::string m, int w, int h) :
        map(c), mapName(m), width(w), height(h){}
    ~CharMap();
    void printCharMap();
    char ** map;
    std::string mapName;
    int width;
    int height;
};


#endif // CHARMAP_H

#include "CharMap.h"
#include<stdlib.h>
#include<iostream>

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
            fin >> (map[i][j]) >> std::noskipws; //dont skip whitespace
        fin >> std::skipws; //skip it again just so we skip linefeed
    }
    //for(int i=0; i<height; i++){ //Uncomment if you have issues reading
    //    for(int j=0; j<width; j++) printf("%c", map[i][j]); printf("\n");};
}

void CharMap::printCharMap(){ //call only after curses is initialized!
//    printw("Read Map: '%s' with dimensions %dx%d!\n",
//            mapName.c_str(), height, width);
//    //Note the c_str is required for C++ Strings to print with printw
//    for(int i=0; i<height; i++){
//        for(int j=0; j<width; j++)
//            printw("%c", map[i][j]);
//        printw("\n");
//    }

    cout<< "Read Map: "<<mapName <<" with dimensions " << height <<"x"<< width <<endl;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++)
            cout<<map[i][j];
        cout<<endl;
    }
}

CharMap::~CharMap(){
    if(map == NULL) return;
    for(int i=0; i<height; i++)
        delete [] map[i];
    delete [] map;
}

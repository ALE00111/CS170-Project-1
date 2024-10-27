#include "problem.h"
#include <iostream>
using namespace std;


Problem::Problem(int puzzle [3][3], int zeroX, int zeroY) {
    //In C++ we can't assign arrays specifically to each other and must do each element one by one
    for(int i = 0; i < 3; ++i) { //Copy over contents to our own array in problem class and copy to inital
        for(int j = 0; j < 3; ++j) {
           array[i][j] = puzzle[i][j];
           inital[i][j] = puzzle[i][j];
        }
    }
    zeroTileX = zeroX;
    zeroTileY = zeroY;
    rows = 3;
    columns = 3;
}

bool Problem::moveUp() {
    //First it can't move up if its at the top
    if(zeroTileY  == 0) {
        //Cannot move up 
        return false;
    }

    //get num that is above zero tile to swap it
    int temp = array[zeroTileY - 1][zeroTileX];

    //Replace above tile with zero
    array[zeroTileY - 1][zeroTileX] = 0;

    //Replace original zero tile location with temp
    array[zeroTileY][zeroTileX] = temp;

    //Set zeroTile locations
    zeroTileY = zeroTileY - 1; //Move Y up
    zeroTileX = zeroTileX; //But x is kept same

    return true;
}

bool Problem::moveDown() {
    //First it can't move down if its at the bottom
    if(zeroTileY  == rows - 1) {
        //Cannot move up 
        return false;
    }

    //get num that is below zero tile to swap it
    int temp = array[zeroTileY + 1][zeroTileX];

    //Replace below tile with zero
    array[zeroTileY + 1][zeroTileX] = 0;

    //Replace original zero tile location with temp
    array[zeroTileY][zeroTileX] = temp;

    //Set zeroTile locations
    zeroTileY = zeroTileY + 1; //Move Y down
    zeroTileX = zeroTileX; //But x is kept same

    return true;
}

bool Problem::moveLeft() {
     //First it can't move left if its at the 0 index for x
    if(zeroTileX  == 0) {
        //Cannot move left
        return false;
    }

    //get num that is left of zero tile to swap it
    int temp = array[zeroTileY][zeroTileX - 1];

    //Replace left tile with zero
    array[zeroTileY][zeroTileX - 1] = 0;

    //Replace original zero tile location with temp
    array[zeroTileY][zeroTileX] = temp;

    //Set zeroTile locations
    zeroTileY = zeroTileY; //Y stays same
    zeroTileX = zeroTileX - 1; // shift x by 1 to left

    return true;
}

bool Problem::moveRight() {
     //First it can't move right if its at the 2 index for x
    if(zeroTileX  == columns -1) {
        //Cannot move left
        return false;
    }

    //get num that is right of zero tile to swap it
    int temp = array[zeroTileY][zeroTileX + 1];

    //Replace right tile with zero
    array[zeroTileY][zeroTileX + 1] = 0;

    //Replace original zero tile location with temp
    array[zeroTileY][zeroTileX] = temp;

    //Set zeroTile locations
    zeroTileY = zeroTileY; //Y stays same
    zeroTileX = zeroTileX + 1; // shift x by 1 to right

    return true;
}

void Problem::setNewArray(int oldarray[3][3]) {
    for(int r = 0; r < 3; ++r) {
        for(int c = 0; c < 3; ++c) {
            array[r][c] = oldarray[r][c];
        }
    }
}

void Problem::printArray() {
    for(int r = 0; r < 3; ++r) {
        for(int c = 0; c < 3; ++c) {
            cout << array[r][c] << " ";
        }
        cout << endl;
    }
}


void Problem::printzeroTileX() {
    cout << zeroTileX << endl;
}

void Problem::printzeroTileY() {
    cout << zeroTileY << endl;
}




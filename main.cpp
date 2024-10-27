#include <iostream>
#include <string>
#include "problem.h"
using namespace std;

void UniformCostSearch(Problem prob);
void AstarMisplaceTile(Problem prob);
void AstarEuclidian(Problem prob);

int main() {
    cout << "Welcome to 8 puzzle solver." << endl;
    cout << "type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle."  << endl;

    // int puzzle [3][3]; //Change these values to match how big you want the puzzle to be
    int num1, num2, num3, num4, num5, num6, num7, num8, num9;
    int zeroX, zeroY;
    bool validMove;

    cout << "Enter your puzzle, use a zero to represent the blank" << endl;
    cout << "Enter the first row, use space or tabs between numbers: ";
    cin >> num1 >> num2 >> num3;
    cout << endl;
    cout << "Enter the second row, use space or tabs between numbers: ";
    cin >> num4 >> num5 >> num6;
    cout << endl;
    cout << "Enter the third row, use space or tabs between numbers: ";
    cin >> num7 >> num8 >> num9;
    cout << endl;

    int puzzle [3][3] = {
        {num1, num2, num3},
        {num4, num5, num6},
        {num7, num8, num9}
    };

    //Representation of eight puzzle
    //indexesX           0  1   2
    // indexesY     0  [ 1, 2 , 3 ]
    //              1  [ 4, 5 , 6 ]
    //              2  [ 7, 8 , 0 ]



    for(int i = 0; i < 3; ++i) { //Copy over contents to our own array in problem class and copy to inital
        for(int j = 0; j < 3; ++j) {
           if(puzzle[i][j] == 0) {
                zeroX = j; //j is reprsented as colums(x)
                zeroY = i; // i is represented as rows(y)
           }
        }
    }
    

    Problem prob(puzzle, zeroX, zeroY);

    //Print out array
    prob.printArray();
    cout << endl;


    //Tests
    //Move up
    // cout << "Moving Up" << endl;
    // validMove = prob.moveUp();
    // if(validMove) {
    //     prob.printArray();
    // }
    // else {
    //     cout << "Can't Move up" <<endl;
    // }
    // cout << endl;
    
    // //Move Down
    // cout << "Moving Down" << endl;
    // validMove = prob.moveDown();
    // if(validMove) {
    //     prob.printArray();
    // }
    //  else {
    //     cout << "Can't Move down" <<endl;
    // }
    // cout << endl;

    // //Move Left
    // cout << "Moving left" << endl;
    // validMove = prob.moveLeft();
    // if(validMove) {
    //     prob.printArray();
    // }
    //  else {
    //     cout << "Can't Move left" <<endl;
    // }
    // cout << endl;

    // //Move Right
    // cout << "Moving right" << endl;
    // validMove = prob.moveRight();
    // if(validMove) {
    //     prob.printArray();
    // }
    //  else {
    //     cout << "Can't Move right" <<endl;
    // }
    // cout << endl;

    return 0;
}



void UniformCostSearch(Problem prob) {
    //Implement unfiorm cost search
}

void AstarMisplaceTile(Problem prob){
    //Impleent A* with Misplaced Tile Heuristic
}

void AstarEuclidian(Problem prob) {
    //Impleent A* with Euclidian Distance
}
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "problem.h"
using namespace std;

void UniformCostSearch(Problem prob);
void AstarMisplaceTile(Problem prob);
void AstarEuclidian(Problem prob);
bool withinFrontier(queue<Problem> frontier, Problem choice);
bool withinExplore(queue<Problem> explore, Problem choice);
bool sameArray(Problem first, Problem second); 
int main() {
    cout << "Welcome to 8 puzzle solver." << endl;
    cout << "Enter your own puzzle."  << endl;

    // int puzzle [3][3]; //Change these values to match how big you want the puzzle to be
    int num1, num2, num3, num4, num5, num6, num7, num8, num9;
    int rowZero, colZero;
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
                rowZero = j; //j is reprsented as colums(x)
                colZero = i; // i is represented as rows(y)
           }
        }
    }
    

    Problem prob(puzzle, rowZero, colZero);

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

    // if(prob.isGoal()){
    //     cout << "Found Goal state. It costed: " << prob.getCost() << endl;
    // }
    // else {
    //     cout <<"firck" << endl;
    // }



    UniformCostSearch(prob);

    return 0;
}

// bool sameArray(Problem first, Problem second) {
//     for(int row = 0; row < 3; ++row) {
//         for(int col = 0; col < 3; ++ col) {
//             if(first.array[row][col] != second.array[row][col]) {
//                 return false;
//             }
//         }
//     }
//     return true;
// }

bool withinFrontier(queue<Problem> frontier, Problem choice){
    queue<Problem> temp = frontier;
    while(!temp.empty()){
        if(temp.front().array == choice.array){
            return true;
        }
        temp.pop();
    }
    return false;
}

bool withinExplore(queue<Problem> explore, Problem choice) {
    queue<Problem> temp = explore;
    while(!temp.empty()){
        if(temp.front().array == choice.array){
            return true;
        }
        temp.pop();
    }
    return false;
}



void UniformCostSearch(Problem prob) {
    //Implement unfiorm cost search
    //Uniform Cost Search is a blind search algorithm that uses the lowest cumulative 
    //cost to find a path from the start to the end goal. For UCS, the h(n) is always 0 
    //but the cost of g(n) is depneding on waht depth the node is on
    queue<Problem> frontier;
    frontier.push(prob); //Initialize frontier with inital state
    queue<Problem> explored;
    //For this problem a priority queue is not needed because you're inserting by cost and the cost only icnreases when the node is expanded 
    //so we must expand all ndoes of the same cost before expanding nodes with higher costs
    

    Problem UpChoice; //Set problem to the possible choice moves
    Problem DownChoice;
    Problem LeftChoice;
    Problem RightChoice;
    Problem temp;

    bool up, down, left, right = false;

    // up = UpChoice.moveUp();
    // down = DownChoice.moveDown();
    // left = LeftChoice.moveLeft();
    // right = RightChoice.moveRight();

    while(!frontier.empty()){
        temp = frontier.front();
        frontier.front().printArray();
        cout << endl;
        frontier.pop();
        //Now removing leaf node and getting all possibilties 
        UpChoice = temp;
        DownChoice = temp;
        LeftChoice = temp;
        RightChoice = temp;
    
        if(temp.isGoal()){
            cout << "Found Goal state. It costed: " << temp.getCost() << endl;
            break;
        }
        explored.push(temp);

        up = UpChoice.moveUp();
        down = DownChoice.moveDown();
        left = LeftChoice.moveLeft();
        right = RightChoice.moveRight();
        //For uniform cost search, the heuristic is always just the depth at which the node is at
        //On top of checking if move is valid, must also check if its repeated
        if(up) {
            if(!withinFrontier(frontier, UpChoice) && !withinExplore(explored, UpChoice)){ //if no duploicate found push into frontier
                frontier.push(UpChoice);
            }
        }
        if(down) {
            if(!withinFrontier(frontier, DownChoice) && !withinExplore(explored, UpChoice)){
                frontier.push(DownChoice);
            }
        }
        if(left) {
            if(!withinFrontier(frontier, LeftChoice) && !withinExplore(explored, UpChoice)){
                frontier.push(LeftChoice);
            }
        }
        if(right) {
            if(!withinFrontier(frontier, RightChoice) && !withinExplore(explored, UpChoice)){
                frontier.push(RightChoice);
            }
        }
    }
}

void AstarMisplaceTile(Problem prob){
    //Impleent A* with Misplaced Tile Heuristic
}

void AstarEuclidian(Problem prob) {
    //Impleent A* with Euclidian Distance
}
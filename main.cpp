#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <utility>
#include "problem.h"
using namespace std;

void UniformCostSearch(Problem prob);
void AstarMisplaceTile(Problem prob);
void AstarEuclidian(Problem prob);
bool withinFrontier(priority_queue<Problem> frontier, Problem choice);
bool withinExplored(priority_queue<Problem> explored, Problem choice);
bool sameArray(Problem first, Problem second); 
int MAX_FRONTIER = 0;

int main() {
    cout << "Welcome to 8 puzzle solver." << endl;
    cout << "Would you like to enter your own puzzle(1) or use deafult(2)?"  << endl;
    // int puzzle [3][3]; //Change these values to match how big you want the puzzle to be
    int num1, num2, num3, num4, num5, num6, num7, num8, num9;
    int rowZero, colZero;
    int chooseType;
    int chooseProb;
    bool validMove;

    cin >> chooseType;
    
    if(chooseType == 1) {
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
    }
    else if (chooseType == 2) {
        //Doable case
        num1 = 0;
        num2 = 1; 
        num3 = 2;
        num4 = 4;
        num5 = 5;
        num6 = 3;
        num7 = 7;
        num8 = 8;
        num9 = 6;
    }

    //Representation of eight puzzle
    //indexesX           0  1   2
    // indexesY     0  [ 1, 2 , 3 ]
    //              1  [ 4, 5 , 6 ]
    //              2  [ 7, 8 , 0 ]

    int puzzle [3][3] = {
        {num1, num2, num3},
        {num4, num5, num6},
        {num7, num8, num9}
    };


    //Find location of 0
    for(int i = 0; i < 3; ++i) { //Copy over contents to our own array in problem class and copy to inital
        for(int j = 0; j < 3; ++j) {
           if(puzzle[i][j] == 0) {
                rowZero = j; //j is reprsented as colums(x)
                colZero = i; // i is represented as rows(y)
           }
        }
    }
    

    Problem prob(puzzle, rowZero, colZero);

    cout << "Enter your choice of algorithm" << endl;
    cout << "1.Uniform Cost Search" << endl;
    cout << "2.A* with the Misplaced Tile heuristic" << endl;
    cout << "3.A* with the Euclidean distance heuristic" << endl;
    cin >> chooseProb; 
    cout << endl;

    if(chooseProb == 1) {
        //Uniform Cost Search is a blind search algorithm that uses the lowest cumulative 
        //cost to find a path from the start to the end goal. For UCS, the h(n) is always 0 
        //but the cost of g(n) is depneding on waht depth the node is on
        UniformCostSearch(prob);
    }
    else if( chooseProb == 2) {
        //A*: A search algorithm that calculates and searches/enqueues nodes based on the lowest heuristic cost. 
        //A heuristic can be any constraint or calculation type we give it. For example, in a classic graph algorithm with A*, 
        //we can use f(n) = h(n) + g(n) where h(n) is the distance for the current node n to the goal state and g(n) is the cost 
        //amount from the start state to the current state. All of this is calculated as the heuristic (i think?...). This would be used 
        //to find the shortest path from start to goal state.


        //A* with the Misplaced Tile heuristic: While using A*, the heuristic we used to figure out what path to take is defined by 
        //g(n): # of actions performed on initial state to reach to current state and h(n) = # of misplaced tile(s). Then the total 
        //cost of that state would be g(n) + h(n)
        AstarMisplaceTile(prob);
    }
    else if(chooseProb == 3) {
        AstarEuclidian(prob);
    }

    return 0;
}

bool sameArray(Problem first, Problem second) {
    for(int row = 0; row < 3; ++row) {
        for(int col = 0; col < 3; ++ col) {
            if(first.array[row][col] != second.array[row][col]) {
                return false;
            }
        }
    }
    return true;
}

bool withinFrontier(priority_queue<Problem> frontier, Problem choice){
    while(!frontier.empty()){
        if(sameArray(frontier.top(), choice)) {
            return true;
        }
        frontier.pop();
    }
    return false;
}

bool withinExplored(priority_queue<Problem> explored, Problem choice) {
    while(!explored.empty()){
        if(sameArray(explored.top(), choice)) {
            return true;
        }
        explored.pop();
    }
    return false;
}

void UniformCostSearch(Problem prob) {
    //Implement unfiorm cost search
    priority_queue<Problem> frontier; //Sort by cost + heuristic values from least to greatest
    frontier.push(prob); //Initialize frontier with inital state
    priority_queue<Problem> explored; //Sort by cost + heuristic values from least to greatest
    //For this problem a priority queue is not needed because you're inserting by cost and the cost only icnreases when the node is expanded 
    //so we must expand all ndoes of the same cost before expanding nodes with higher costs
    

    Problem UpChoice; //Set problem to the possible choice moves
    Problem DownChoice;
    Problem LeftChoice;
    Problem RightChoice;
    Problem tempFrontierFront;

    bool up, down, left, right = false;


    while(!frontier.empty()){
        tempFrontierFront = frontier.top();
        cout << "The best state to expand with g(n) = " << frontier.top().getCost() << " and h(n) = " << frontier.top().getHeurisitc() << " is... " << endl;
        frontier.top().printArray();
        frontier.pop();
        //Now removing leaf node and getting all possibilties 
        UpChoice = tempFrontierFront;
        DownChoice = tempFrontierFront;
        LeftChoice = tempFrontierFront;
        RightChoice = tempFrontierFront;
    
        if(tempFrontierFront.isGoal()){
            cout << "Found Goal state!" << endl;
            cout << "The Depth of the Goal Node: " << tempFrontierFront.getCost() << endl;
            cout << "Max number of Nodes in frontier at one time: " << MAX_FRONTIER << endl;
            cout << "Number of Nodes expanded/explored: " << explored.size() << endl;
            break;
        }

        explored.push(tempFrontierFront);
        cout << "Expanding this node" << endl;
        cout << endl;

        up = UpChoice.moveUp();
        down = DownChoice.moveDown();
        left = LeftChoice.moveLeft();
        right = RightChoice.moveRight();
        //For uniform cost search, the heuristic is always just the depth at which the node is at
        //On top of checking if move is valid, must also check if its repeated
         if(right) {
            if(!withinFrontier(frontier, RightChoice) && !withinExplored(explored, RightChoice)){
                frontier.push(RightChoice);
            }
        }
         if(left) {
            if(!withinFrontier(frontier, LeftChoice) && !withinExplored(explored, LeftChoice)){
                frontier.push(LeftChoice);
            }
        }
        if(up) {
            if(!withinFrontier(frontier, UpChoice) && !withinExplored(explored, UpChoice)){ //if no duploicate found push into frontier
                frontier.push(UpChoice);
            }
        }
        if(down) {
            if(!withinFrontier(frontier, DownChoice) && !withinExplored(explored, DownChoice)){
                frontier.push(DownChoice);
            }
        }

        if(frontier.size() > MAX_FRONTIER) {
            MAX_FRONTIER = frontier.size();
        }
    }
}



void AstarMisplaceTile(Problem prob){
    //Impleent A* with Misplaced Tile Heuristic
    // We add initial state to frontier and pop it off and expand it, when expanded we caluclate the heuristic and get its f(n) value
    // From there, we insert it into the frontier by priority and continue to pop off and expand again until goal state found
    //First we need to initalize a priority queue
    priority_queue<Problem> frontier;
    prob.setHeuristic(prob.numMisplacedTiles());
    frontier.push(prob); //Initialize frontier with inital state
    priority_queue<Problem> explored;

    Problem UpChoice; //Set problem to the possible choice moves
    Problem DownChoice;
    Problem LeftChoice;
    Problem RightChoice;
    Problem tempFrontierFront;

    bool up, down, left, right = false;


    while(!frontier.empty()){
        tempFrontierFront = frontier.top();
        cout << "The best state to expand with g(n) = " << frontier.top().getCost() << " and h(n) = " << frontier.top().getHeurisitc() << " is... " << endl;
        frontier.top().printArray();
        frontier.pop();
        //Now removing leaf node and getting all possibilties 
        UpChoice = tempFrontierFront;
        DownChoice = tempFrontierFront;
        LeftChoice = tempFrontierFront;
        RightChoice = tempFrontierFront;
    
        if(tempFrontierFront.isGoal()){
            cout << "Found Goal state!" << endl;
            cout << "The Depth of the Goal Node: " << tempFrontierFront.getCost() << endl;
            cout << "Max number of Nodes in frontier at one time: " << MAX_FRONTIER << endl;
            cout << "Number of Nodes expanded/explored: " << explored.size() << endl;
            break;
        }

        explored.push(tempFrontierFront);
        cout << "Expanding this node" << endl;
        cout << endl;

        up = UpChoice.moveUp();
        down = DownChoice.moveDown();
        left = LeftChoice.moveLeft();
        right = RightChoice.moveRight();

        //Now we get the heuristic by caluclating the number of misplaced tiles of each operator
        UpChoice.setHeuristic(UpChoice.numMisplacedTiles());
        DownChoice.setHeuristic(DownChoice.numMisplacedTiles());
        LeftChoice.setHeuristic(LeftChoice.numMisplacedTiles());
        RightChoice.setHeuristic(RightChoice.numMisplacedTiles());


        //For uniform cost search, the heuristic is always just the depth at which the node is at
        //On top of checking if move is valid, must also check if its repeated
        if(right) {
            if(!withinFrontier(frontier, RightChoice) && !withinExplored(explored, RightChoice)){
                frontier.push(RightChoice);
            }
        }
        if(left) {
            if(!withinFrontier(frontier, LeftChoice) && !withinExplored(explored, LeftChoice)){
                frontier.push(LeftChoice);
            }
        }
        if(up) {
            if(!withinFrontier(frontier, UpChoice) && !withinExplored(explored, UpChoice)){ //if no duploicate found push into frontier
                frontier.push(UpChoice);
            }
        }
        if(down) {
            if(!withinFrontier(frontier, DownChoice) && !withinExplored(explored, DownChoice)){
                frontier.push(DownChoice);
            }
        }

        if(frontier.size() > MAX_FRONTIER) {
            MAX_FRONTIER = frontier.size();
        }
    }
}

void AstarEuclidian(Problem prob) {
    //Impleent A* with Euclidian Distance
    // We add initial state to frontier and pop it off and expand it, when expanded we caluclate the heuristic and get its f(n) value
    // From there, we insert it into the frontier by priority and continue to pop off and expand again until goal state found
    //First we need to initalize a priority queue
    priority_queue<Problem> frontier;
    prob.setHeuristic(prob.computeTotalHeuristic());
    frontier.push(prob); //Initialize frontier with inital state
    priority_queue<Problem> explored;

    Problem UpChoice; //Set problem to the possible choice moves
    Problem DownChoice;
    Problem LeftChoice;
    Problem RightChoice;
    Problem tempFrontierFront;

    bool up, down, left, right = false;


    while(!frontier.empty()) {
        tempFrontierFront = frontier.top();
        frontier.top().printArray();
        frontier.pop();
        //Now removing leaf node and getting all possibilties 
        UpChoice = tempFrontierFront;
        DownChoice = tempFrontierFront;
        LeftChoice = tempFrontierFront;
        RightChoice = tempFrontierFront;
    
        if(tempFrontierFront.isGoal()) {
            cout << "Found Goal state!" << endl;
            cout << "The Depth of the Goal Node: " << tempFrontierFront.getCost() << endl;
            cout << "Max number of Nodes in frontier at one time: " << MAX_FRONTIER << endl;
            cout << "Number of Nodes expanded/explored: " << explored.size() << endl;
            break;
        }

        explored.push(tempFrontierFront);
        cout << "Expanding this node" << endl;
        cout << endl;

        up = UpChoice.moveUp();
        down = DownChoice.moveDown();
        left = LeftChoice.moveLeft();
        right = RightChoice.moveRight();

        //Now we get the heuristic by caluclating Euclidean distance (sqrt(x2-x1)^2 + (y2-y1)^2)
        UpChoice.setHeuristic(UpChoice.computeTotalHeuristic());  // new func .euclideanDist ? 
        DownChoice.setHeuristic(DownChoice.computeTotalHeuristic());
        LeftChoice.setHeuristic(LeftChoice.computeTotalHeuristic());
        RightChoice.setHeuristic(RightChoice.computeTotalHeuristic());


        //For uniform cost search, the heuristic is always just the depth at which the node is at
        //On top of checking if move is valid, must also check if its repeated
        if(right) {
            if(!withinFrontier(frontier, RightChoice) && !withinExplored(explored, RightChoice)){
                frontier.push(RightChoice);
            }
        }
        if(left) {
            if(!withinFrontier(frontier, LeftChoice) && !withinExplored(explored, LeftChoice)){
                frontier.push(LeftChoice);
            }
        }
        if(up) {
            if(!withinFrontier(frontier, UpChoice) && !withinExplored(explored, UpChoice)){ //if no duploicate found push into frontier
                frontier.push(UpChoice);
            }
        }
        if(down) {
            if(!withinFrontier(frontier, DownChoice) && !withinExplored(explored, DownChoice)){
                frontier.push(DownChoice);
            }
        }

        if(frontier.size() > MAX_FRONTIER) {
            MAX_FRONTIER = frontier.size();
        }
    }
}


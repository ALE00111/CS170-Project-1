
class Problem {
    public:
        Problem();
        Problem(int puzzle [3][3], int zeroX, int zeroY);
        void printArray() const;
        bool moveUp(); //Moves 0 tile up
        bool moveDown(); // Moves 0 tile down
        bool moveLeft(); //Moves 0 tile left
        bool moveRight(); //Moves 0 tile right
        void printzeroTileX() const;
        void printzeroTileY() const;
        void setNewArray(int oldarray[3][3]);
        void setHeuristic(int hVal);
        int getHeurisitc();
        int estimatedCost();
        bool isGoal();
        int getValue(int y, int x);
        int getCost();
        int numMisplacedTiles();
        //Overloading Operators for priority queue cause it can't make comparisons with other variables of type Problem
        bool operator<(const Problem& copy) const;
        // bool operator>(const Problem& copy) const;
        int array [3][3];
        int goal [3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 0}
        };
        // Helper function to get Goal coordinates
        pair<int, int> goalCoordinates(int puzzleNum);
        double euclideanHeuristic();
        
    private:
        int zeroTileX; //x coordinate of the 0 tile
        int zeroTileY; //y coordinate of the 0 tile
        int rows;
        int columns;
        int cost;
        int heuristic;
        int inital[3][3];
};
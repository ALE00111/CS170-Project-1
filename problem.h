
class Problem {
    public:
        Problem();
        Problem(int puzzle [3][3], int zeroX, int zeroY);
        void printArray();
        bool moveUp(); //Moves 0 tile up
        bool moveDown(); // Moves 0 tile down
        bool moveLeft(); //Moves 0 tile left
        bool moveRight(); //Moves 0 tile right
        void printzeroTileX();
        void printzeroTileY();
        void setNewArray(int oldarray[3][3]);
        bool isGoal();
        int getValue(int y, int x);
        int getCost();
        int array [3][3];
        int goal [3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 0}
        };
        
    private:
        int zeroTileX; //x coordinate of the 0 tile
        int zeroTileY; //y coordinate of the 0 tile
        int rows;
        int columns;
        int cost;
        int inital[3][3];
};
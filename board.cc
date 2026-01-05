export module Board; 

import <memory>;
import <string>;
import <vector>;
import <iostream>;

import Link; 
import Posn; 
import Square;
import MoveResult;

export class Board {
    static const int DIMENSIONS = 8; //can change this to modify board size
    std::vector<std::vector<std::unique_ptr<Square>>> grid; 
    private: 
        // initializes the grid with squares and special squares
        void initializeGrid(); 
    public: 
        //constructor
        Board(); 
        
        //getter for square at given position, returns nullptr if out of bounds
        Square* getSquare(Posn posn) const;

        //overloaded getter for square at given x,y coordinates
        Square* getSquare(int x, int y) const;

        // returns the vector representation of the board
        std::vector<std::vector<std::unique_ptr<Square>>>& getGrid(); 

        // returns the dimension of the square board
        static int getDimensions();

        //returns true if link was placed successfully, assumes validation already occurred
        bool placeLink(Link* link, Posn posn); 

        //finds the position of a link by its alias, returns (-1,-1) if not found
        Posn findLink(char alias) const; 

        //validates if a move from 'from' to 'to' by 'playerNum' is valid
        bool isValidMove(Posn from, Posn to, int playerNum) const; 

        //Logic for a move in the game
        MoveResult moveLink(Posn from, Posn to); 

        //checks if a position is within the board boundaries
        bool inBounds(Posn posn) const; 

        //checks if a position is a server port
        bool isServerPort(Posn posn) const; 

        //checks if a position is a firewall
        bool isFirewall(Posn posn) const;

        //checks if a position is a barrier
        bool isBarrier(Posn posn) const; 

        //checks if a position is on the opponent's edge for the given player
        bool isOpponentEdge(Posn posn, int playerNum) const; 

        //displays board, printing from top to bottom (0,0) to (7,7)
        friend std::ostream& operator<<(std::ostream& out, const Board& board);

};

export std::ostream& operator<<(std::ostream& out, const Board& board);

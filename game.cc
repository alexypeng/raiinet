export module Game; 

import <memory>; 
import <string>; 
import <vector>;
import <map>;
import <iostream>;
import Player; 
import Link;
import Ability;
import Board; 
import Enums;
import Square;
import Posn;
import LinkBoost; 
import Firewall; 
import Download; 
import Scan; 
import Polarize; 
import Diagonal;
import Barrier;
import Posn;
import MoveResult;
import AbilityResult;
import Swap;
import ISubject;

export class Game : public ISubject {
    std::unique_ptr<Player> p1; 
    std::unique_ptr<Player> p2;
    Player* currPlayer; 
    Player* otherPlayer;
    Board board; 
    bool gameOver; 
    bool abilityPlayed = false; 
    bool graphics = false; 

    private:
        //helper to initialize Player Links
        void initLinks(Player* p, const std::string& linkOrder);

        //helper to initalize Player Abilities
        void initAbilities(Player* p, const std::string& abilityOrder);

        //helper to parse a Link from stdin
        Link* parseLink(char info); 

        //helper to parse a Square from stdin
        Square* parseSquare(const std::string& info);

        //helper to parse two Links from stdin
        std::pair<Link*, Link*> parseTwoLinks(const std::string& info);

        //helper to validate an Ability order argument
        bool validAbilityArg(const std::string& arg);

        //helper to validate a Link order argument
        bool validLinkArg(const std::string& arg);

    public: 
        //constructor to initialize a game
        Game(); 

        //initializes game using command args
        void initGame(int argc, char* args[]); 

        //initializes players and their links/abilities
        void initPlayers(const std::string p1Links, const std::string p2Links, const std::string p1Abilities, const std::string p2Abilities); 

        //switches current player
        void switchTurn(); 

        //checks if win condition is met
        void checkWinCondition(); 

        //getter for current player
        Player* getCurrentPlayer() const; 

        //getter for opponent player
        Player* getOpponent() const; 

        //getter for board
        Board* getBoard(); 

        //getter for gameOver boolean
        bool isGameOver(); 

        //executes a move for the current player, returns the result of the move
        MoveResult playMove(char c, Direction dir, Direction dir2 = Direction::NONE); 

        //executes an ability for the current player, returns true if successful, false otherwise
        AbilityResult playAbility(int index, const std::string& targetInfo);

        //checks if the current player owns the link represented by character c
        bool currentPlayerOwnsLink(char c) const; 
};

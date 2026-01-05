export module Link;

import <string>;
import <iostream>;
import Enums;
import Posn;

export class Link {
    std::string id = ""; //id formed by the type + strength (eg. "D4")
    char alias; //single character representing the link (eg. 'a', 'B')
    LinkType type; //DATA or VIRUS
    int strength;
    Posn posn; 
    int owner; //int representing player number (1 or 2) 

    //booleans to track state of the link
    bool revealed = false;
    bool downloaded = false;
    bool polarized = false;
    bool linkBoosted = false;
    bool movesDiagonally = false;

    public: 
        Link(char alias, LinkType type, int strength, Posn posn, int owner);
        
        //getters
        std::string getId() const;
        LinkType getType() const;
        int getStrength() const;
        Posn getPosn() const;
        int getOwner() const;
        bool isRevealed() const;
        bool isDownloaded() const;
        bool isPolarized() const;
        bool isLinkBoosted() const;
        bool canMoveDiagonally() const;
        char getAlias() const; 

        //setters
        void reveal();
        void download();
        void polarize();
        void boostLink();
        void allowDiagonalMovement();
        void setStrength(int strength);
        void move(Posn newPosn);
        void setAlias(char c); 

        friend std::ostream& operator<<(std::ostream& out, const Link& link); 
};

export std::ostream& operator<<(std::ostream& out, const Link& link); 

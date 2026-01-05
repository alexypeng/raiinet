export module Square;

import Posn;
import Link;

export class Square {
    Posn posn;
    Link* link; // Pointer to a Link object owned by Player
    int serverPortOwner = 0; // 0 if unowned, 1 or 2 for player ownership
    int firewallOwner = 0;
    bool serverPort = false;
    bool firewall = false;
    bool barrier = false; 

    public: 
        // constructors
        Square(int row, int col);

        // constructor using Posn
        Square(Posn posn);

        // state of squares

        //checks if square is Empty (no link present)
        bool isEmpty() const;

        //checks if square is a firewall
        bool isFirewall() const;

        //checks if square is a barrier
        bool isBarrier() const;

        //checks if square is a server port
        bool isServerPort() const;
        
        //Link management -> directly setting/removing link pointer, not validating moves
        
        // sets link on square
        void setLink(Link* link);

        // gets link on square
        Link* getLink() const;

        // removes link from square and returns pointer to Link
        Link* removeLink();

        // sets square as a server port for given player
        void setServerPort(int playerNum);

        // gets owner of server port
        int getServerPortOwner() const;

        // gets owner of firewall
        int getFirewallOwner() const; 

        // sets square as a barrier
        void setBarrier();

        // sets square as a firewall
        void setFirewall(int playerNum);

        // getter for position
        Posn getPosn() const;

        // checking if a link can enter the square, validating moves
        bool canEnterDuringMove(Link* movingLink) const;
};

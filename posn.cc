export module Posn;

import Enums;

export struct Posn {
    int x; 
    int y; 

    Posn(int x, int y);
    bool operator==(const Posn& other) const; 
    Posn move(int player, Direction dir, bool boosted) const;
};

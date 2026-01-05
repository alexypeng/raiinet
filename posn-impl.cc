module Posn; 

import Enums;

Posn::Posn(int x, int y) : x(x), y(y) {}

bool Posn::operator==(const Posn& other) const {
    return this->x == other.x && this->y == other.y;
}

//movement assumes (0,0) is top-left, (7,7) bottom right
Posn Posn::move(int player, Direction dir, bool boosted) const {
    int dist = (boosted? 2 : 1);
    switch (dir) {
        case Direction::UP:
            return (player == 1? Posn(x - dist, y) : Posn(x + dist, y));
        case Direction::DOWN:
            return (player == 1? Posn(x + dist, y) : Posn(x - dist, y));
        case Direction::LEFT:
            return (player == 1? Posn(x, y - dist) : Posn(x, y + dist));
        case Direction::RIGHT:
            return (player == 1? Posn(x, y + dist) : Posn(x, y - dist));
        default:
            return *this; // No movement if direction is invalid
    }
}

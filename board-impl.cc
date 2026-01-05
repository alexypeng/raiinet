module Board; 

import <memory>;
import <vector>;
import <iostream>;

import Link;
import Posn;
import Square;
import MoveResult; 
import Enums;

using std::cout, std::endl;

Board::Board() {
    grid.resize(DIMENSIONS);
    for (auto& row: grid) {
        row.resize(DIMENSIONS);
    }
    initializeGrid(); 
}

void Board::initializeGrid() {
    //create all squares
    for (int i = 0; i < DIMENSIONS; i++) {
        for (int j = 0; j < DIMENSIONS; j++) {
            grid[i][j] = std::make_unique<Square>(Posn{i, j}); 
        }
    }

    //set up server ports -> p2 starts row 0, p1 starts at row 7
    grid[0][3]->setServerPort(2);
    grid[0][4]->setServerPort(2);
    grid[7][3]->setServerPort(1);
    grid[7][4]->setServerPort(1);
}

Square* Board::getSquare(Posn posn) const {
    if (inBounds(posn)) {
        return grid[posn.x][posn.y].get(); 
    }
    return nullptr;
}

Square* Board::getSquare(int x, int y) const {
    return getSquare(Posn{x,y});
}

std::vector<std::vector<std::unique_ptr<Square>>>& Board::getGrid() {
    return grid;
}

int Board::getDimensions() {
    return DIMENSIONS;
}

bool Board::placeLink(Link* link, Posn posn) {
    Square* square = getSquare(posn);
    if (!square) return false; //if square is not valid on grid

    if (square->isEmpty()) {
        square->setLink(link);
        link->move(posn); //update link's position
        return true;
    }

    return false; //if square is occupied
}

Posn Board::findLink(char alias) const {
    for (int i = 0; i < DIMENSIONS; i++) {
        for (int j = 0; j < DIMENSIONS; j++) {
            Square* square = grid[i][j].get(); 
            if (!square->isEmpty()) {
                Link* link = square->getLink(); 
                if (link->getAlias() == alias) {
                    return Posn{i, j}; 
                }
            }
        }
    }
    return Posn{-1, -1}; //indicates not found
}

bool Board::isValidMove(Posn from, Posn to, int playerNum) const{
    //if the initial square has no link or square doesn't exist
    Square* fromSquare = getSquare(from);
    if (!fromSquare || fromSquare->isEmpty()) {
        return false; 
    }

    Link* movingLink = fromSquare->getLink();
    if (!movingLink) return false; 
    if (movingLink->getOwner() != playerNum) {
        return false;
    } //link does not belong to player

    int xDiff = abs(to.x - from.x);
    int yDiff = abs(to.y - from.y);

    bool isDiagonalMove = (xDiff > 0 && yDiff > 0);
    bool isBoosted = movingLink->isLinkBoosted();
    bool canDiagonal = movingLink->canMoveDiagonally();

    // Check if diagonal move is allowed
    if (isDiagonalMove && !canDiagonal) return false;

    // Check move distance
    if (isDiagonalMove) {
        // Diagonal: must be exactly 1 in each direction
        if (!isBoosted && (xDiff != 1 || yDiff != 1)) {
            return false;
        }
        else if (isBoosted && (xDiff != 2 || yDiff != 2)) { 
            return false; 
        }
    } else {
        // Straight move
        int totalDist = xDiff + yDiff;
        if (isBoosted) {
            // Boosted have to move 2 spaces
            if (totalDist != 2) return false;
        } else {
            // Normal: exactly 1 space
            if (totalDist != 1) return false;
        }
    }

    // Edge case: moving off the board
    if (!inBounds(to)) {        
        return isOpponentEdge(to, playerNum);
    }

    Square* toSquare = getSquare(to);
    if (!toSquare) {
        cout << "Square doesn't exist at: (" << to.x << "," << to.y  << ")" << endl;
        return false;
    } //if square doesn't exist

    if (toSquare->getLink() && toSquare->getLink()->getOwner() == playerNum) {
        cout << "Square is occupied by one of your pieces." << endl;
        return false; //cannot move onto square occupied by own link
    }

    if (toSquare->isServerPort() && toSquare->getServerPortOwner() == playerNum) {
        cout << "Cannot move onto your own server port!" << endl;
        return false; //cannot move onto own server port
    }

    if (toSquare->isBarrier()) return false; //can't move onto a barrier
    return true; 
}

MoveResult Board::moveLink(Posn from, Posn to) {
    MoveResult res;

    //Validating initial square
    Square* fromSquare = getSquare(from);
    if (!fromSquare || fromSquare->isEmpty()) {
        res.success = false; 
        res.msg = "Invalid move: No link at the source position.";
        return res;
    }

    Link* movingLink = fromSquare->getLink();
    int movingPlayer = movingLink->getOwner();

    //Validating move
    if (!isValidMove(from, to, movingPlayer)) {
        res.success = false; 
        res.msg = "Invalid move";
        return res;
    }

    //if moving off the board (to opponent edge)
    if (!inBounds(to)) { //should be confirmed to be opponent edge (already validated)
        res.success = true;
        res.linkDownloaded = true;
        res.msg = "Link downloaded by reaching opponent's edge!";
        res.downloadedBy = movingPlayer; 
        res.movedOffOpponentEdge = true;
        fromSquare->removeLink();
        return res;
    }

    Square* toSquare = getSquare(to);

    //if moving into opponent's server port
    if (toSquare->isServerPort()) { //should be opponent's server port due to validation
        res.success = true;
        res.linkDownloaded = true;
        res.movedToServerPort = true; 
        res.msg = "Link downloaded by reaching opponent's server port!";
        fromSquare->removeLink();
        res.downloadedBy = (movingPlayer == 1? 2: 1); //downloaded by opponent
        return res;
    }

    //if battle occurs
    Link* targetLink = toSquare->getLink();
    if (targetLink) {
        movingLink->reveal();
        targetLink->reveal();

        res.linksBattled = true;
        if (movingLink->getStrength() >= targetLink->getStrength()) {
            res.winner = movingLink;
            res.loser = targetLink;
            toSquare->setLink(fromSquare->removeLink());
            res.msg = "Battle won! Moved to target square.";
        } else {
            fromSquare->removeLink();
            res.winner = targetLink;
            res.loser = movingLink;
            res.msg = "Battle lost! Link removed from the board.";
        }
        res.linkDownloaded = true;
        res.success = true;
        res.downloadedBy = res.winner->getOwner();
    } else {
         //if moving to an empty square
        toSquare->setLink(fromSquare->removeLink());
        res.success = true;
        res.msg = "Move successful to empty square.";
    }

    //if square is a firewall
    if (toSquare->isFirewall()) {
        res.msg += " Square is a firewall!";
        res.firewallOwner = toSquare->getFirewallOwner();
        res.movedToFirewall = true;
        if (toSquare->getFirewallOwner() != movingPlayer) {
            movingLink->reveal(); 
            if (movingLink->getType() == LinkType::VIRUS) {
                res.linkDownloaded = true;
                res.downloadedBy = movingLink->getOwner();
                res.msg += " Player downloaded their own virus.";
                toSquare->removeLink();
            }
        } 
    } 

    return res;

}

bool Board::inBounds(Posn posn) const {
    return posn.x >= 0 && posn.x < DIMENSIONS && posn.y >= 0 && posn.y < DIMENSIONS;
}

bool Board::isServerPort(Posn posn) const {
    Square* square = getSquare(posn);
    if (square) {
        return square->isServerPort();
    }
    return false; 
}

bool Board::isFirewall(Posn posn) const {
    Square* square = getSquare(posn);
    if (square) {
        return square->isFirewall();
    }
    return false;
}

bool Board::isBarrier(Posn posn) const {
    Square* square = getSquare(posn);
    if (square) {
        return square->isBarrier();
    }
    return false;
}

bool Board::isOpponentEdge(Posn posn, int playerNum) const {
    cout << "checking opponent edge for player " << playerNum << " at position (" << posn.x << "," << posn.y << ")" << endl;
    if (playerNum == 1 && posn.x == -1) return true; 
    if (playerNum == 2 && posn.x == DIMENSIONS) return true;

    return false; 
}

std::ostream& operator<<(std::ostream& out, const Board& board) {
    out << "========" << std::endl;
    for (int i = 0; i < Board::DIMENSIONS; i++) {
        for (int j = 0; j < Board::DIMENSIONS; j++) {
            Square* square = board.grid[i][j].get(); 
            //can modify symbols after further implementation
            if (!square->isEmpty()) {
                Link* link = square->getLink(); 
                out << link->getAlias(); 
            } else if (square->isServerPort()) {
                out << "S"; //can replace if needed
            } else if (square->isFirewall()) {
                if (square->getFirewallOwner() == 1) {
                    out << "m"; //player 1 firewall
                } else {
                    out << "w"; //player 2 firewall
                }
                out << "F"; //can replace if needed
            } else if (square->isBarrier()) {
                out << "B"; //can replace if needed
            } else {
                out << "."; 
            }
        }
        out << std::endl;
    }
    out << "========" << std::endl;
    return out; 
}

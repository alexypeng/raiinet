module Square; 

import Posn; 
import Link;

Square::Square(int row, int col): posn{row, col}, link{nullptr} {}
Square::Square(Posn posn): posn{posn}, link{nullptr} {}

bool Square::isEmpty() const {
    return link == nullptr; 
}

bool Square::isFirewall() const {
    return firewall; 
}

bool Square::isBarrier() const {
    return barrier; 
}

bool Square::isServerPort() const {
    return serverPort; 
}

void Square::setLink(Link* link) {
    this->link = link; 
}

Link* Square::getLink() const {
    return link; 
}

//returns the Link pointer and removes it from the square
Link* Square::removeLink() {
    Link* temp = link; 
    link = nullptr; 
    return temp; 
}

void Square::setServerPort(int playerNum) {
    serverPort = true; 
    serverPortOwner = playerNum; 
}

int Square::getServerPortOwner() const {
    return serverPortOwner; 
}

int Square::getFirewallOwner() const {
    return firewallOwner; 
}

void Square::setBarrier() {
    barrier = true; 
}

void Square::setFirewall(int playerNum) {
    firewall = true; 
    firewallOwner = playerNum;
}

Posn Square::getPosn() const {
    return posn; 
}

bool Square::canEnterDuringMove(Link* movingLink) const {
    if (isBarrier()) return false; 
    if (isServerPort()) {
        if (getServerPortOwner() != movingLink->getOwner()) {
            return true; 
        } else {
            return false; 
        }
    }
    if (isEmpty()) return true;
    return link->getOwner() != movingLink->getOwner();
}

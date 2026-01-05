module Link;

import <string>;
import Enums;

using std::string;

Link::Link(char alias, LinkType type, int strength, Posn posn, int owner):
    alias(alias), type(type), strength(strength), posn(posn), owner(owner) {
    // Form ID based on type and strength
    id = (type == LinkType::DATA ? "D" : "V") + std::to_string(strength);
}

string Link::getId() const {
    return id;
}

LinkType Link::getType() const {
    return type;
}

int Link::getStrength() const {
    return strength;
}

Posn Link::getPosn() const {
    return posn;
}

int Link::getOwner() const {
    return owner;
}

char Link::getAlias() const {
    return alias;
}

bool Link::isRevealed() const {
    return revealed;
}

bool Link::isDownloaded() const {
    return downloaded;
}

bool Link::isPolarized() const {
    return polarized;
}

bool Link::isLinkBoosted() const {
    return linkBoosted;
}

bool Link::canMoveDiagonally() const {
    return movesDiagonally;
}

void Link::reveal() {
    revealed = true;
}

void Link::download() {
    downloaded = true;
}

void Link::polarize() {
    polarized = true;
    //flipping type
    if (type == LinkType::DATA) {
        type = LinkType::VIRUS;
    } else {
        type = LinkType::DATA;
    }
    //updating ID
    id = (type == LinkType::DATA ? "D" : "V") + std::to_string(strength);
}

void Link::boostLink() {
    linkBoosted = true;
}

void Link::allowDiagonalMovement() {
    movesDiagonally = true;
}

void Link::setStrength(int newStrength) {
    strength = newStrength;
    // Update ID to reflect new strength
    id = (type == LinkType::DATA ? "D" : "V") + std::to_string(strength);
}

void Link::move(Posn newPosn) {
    posn = newPosn;
}

void Link::setAlias(char c) {
    alias = c;
}

std::ostream& operator<<(std::ostream& out, const Link& link) {
    out << link.alias << ": " << link.id; 
    return out;
}

module Ability; 

import Link;
import Square; 
import AbilityResult;

Ability::Ability(int owner) : used{false} , owner{owner}{}

bool Ability::isUsed() const {
    return used; 
}

void Ability::markUsed() {
    used = true;
}

int Ability::getOwner() const {
    return owner;
}

// Default implementations - return failure if not overridden
AbilityResult Ability::activate() {
    return AbilityResult::failure();
}

AbilityResult Ability::activate(Link* target) {
    return AbilityResult::failure();
}

AbilityResult Ability::activate(Square* target) {
    return AbilityResult::failure();
}

AbilityResult Ability::activate(Link* link1, Link* link2) {
    return AbilityResult::failure();
}

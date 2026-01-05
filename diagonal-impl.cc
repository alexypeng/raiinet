module Diagonal;

import Ability;
import Link;
import Square;

Diagonal::Diagonal(int owner) : Ability(owner) {}

AbilityResult Diagonal::activate(Link* target) {
    if (used) return AbilityResult::failure();
    AbilityResult res = AbilityResult::diagonal(target, owner);
    if (res.success) used = true;
    return res;
}

const char* Diagonal::getName() const{
    return "Diagonal";
}

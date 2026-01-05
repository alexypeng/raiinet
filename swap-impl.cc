module Swap;

import Ability;
import Link;
import AbilityResult;

Swap::Swap(int owner) : Ability(owner) {}

AbilityResult Swap::activate(Link* link1, Link* link2) {
    if (used) return AbilityResult::failure();
    AbilityResult res = AbilityResult::swap(link1, link2, owner);
    if (res.success) used = true;
    return res;
}

const char* Swap::getName() const {
    return "Swap"; 
}

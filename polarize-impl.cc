module Polarize; 

import Ability;
import Link;
import Square;

Polarize::Polarize(int owner) : Ability{owner} {}

AbilityResult Polarize::activate(Link* target) {
    if (used) return AbilityResult::failure();
    AbilityResult res = AbilityResult::polarize(target);
    if (res.success) used = true;
    return res;
}

const char* Polarize::getName() const {
    return "Polarize";
}

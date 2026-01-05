module Scan;

import Ability;
import Link;
import Square;

Scan::Scan(int owner) : Ability{owner} {}

AbilityResult Scan::activate(Link* target) {
    if (used) return AbilityResult::failure();
    AbilityResult res = AbilityResult::scan(target);
    if (res.success) used = true;
    return res;
}

const char* Scan::getName() const {
    return "Scan";
}

module LinkBoost;

import Ability;
import Link;
import AbilityResult;

LinkBoost::LinkBoost(int owner) : Ability{owner} {}

AbilityResult LinkBoost::activate(Link* target) {
    if (used) return AbilityResult::failure();
    AbilityResult res = AbilityResult::linkBoost(target, owner);
    if (res.success) used = true;
    return res;
}

const char* LinkBoost::getName() const {
    return "Link Boost";
}

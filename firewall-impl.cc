module Firewall; 

import Ability;
import Square; 
import AbilityResult;

Firewall::Firewall(int owner): Ability{owner} {}

AbilityResult Firewall::activate(Square* target) {
    if (used) return AbilityResult::failure();
    AbilityResult res = AbilityResult::firewall(target);
    if (res.success) used = true;
    return res;
}

const char* Firewall::getName() const {
    return "Firewall";
}

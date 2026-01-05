module Barrier; 

import Ability;  
import Square; 
import AbilityResult;

Barrier::Barrier(int owner) : Ability(owner) {}

AbilityResult Barrier::activate(Square* target) {
    if (used) return AbilityResult::failure();
    AbilityResult res = AbilityResult::barrier(target);
    if (res.success) used = true;
    return res;
}

const char* Barrier::getName() const {
    return "Barrier";
}

module Download; 

import Ability;
import Link;
import AbilityResult; 

Download::Download(int owner): Ability(owner) {}

AbilityResult Download::activate(Link* target) {
    if (used) return AbilityResult::failure();
    AbilityResult res = AbilityResult::download(target, owner);
    if (res.success) used = true;
    return res;
}

const char* Download::getName() const {
    return "Download"; 
}

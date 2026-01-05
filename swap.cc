export module Swap; 

import Ability; 
import Link; 
import AbilityResult;

export class Swap: public Ability {
    public: 
        Swap(int owner);
        AbilityResult activate(Link* link1, Link* link2) override;
        const char* getName() const override;
};

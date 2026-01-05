export module Diagonal; 

import Ability; 
import Link; 
import AbilityResult; 

export class Diagonal : public Ability {
    public: 
        Diagonal(int owner);
        AbilityResult activate(Link* target) override;
        const char* getName() const override;
};

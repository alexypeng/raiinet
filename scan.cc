export module Scan; 

import Ability; 
import Link; 
import AbilityResult;

export class Scan : public Ability {
    public: 
        Scan(int owner); 
        AbilityResult activate(Link* target) override;
        const char* getName() const override;;
};

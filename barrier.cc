export module Barrier; 

import Ability; 
import Square; 
import AbilityResult;

export class Barrier : public Ability {
    public:
        Barrier(int owner);
        AbilityResult activate(Square* target) override;
        const char* getName() const override;
};

export module Polarize;

import Ability;
import Link;
import AbilityResult;

export class Polarize : public Ability{
    public: 
        Polarize(int owner);
        AbilityResult activate(Link* target) override;
        const char* getName() const override;
};

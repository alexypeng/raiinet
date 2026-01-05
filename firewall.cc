export module Firewall;

import Ability; 
import Square;
import AbilityResult;

export class Firewall : public Ability {
    public: 
    Firewall(int owner);
    AbilityResult activate(Square* target) override;
    const char* getName() const override;
};

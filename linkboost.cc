export module LinkBoost;

import Ability;
import Link;
import AbilityResult;

export class LinkBoost: public Ability {
    public:
        LinkBoost(int owner);
        AbilityResult activate(Link* target) override;
        const char* getName() const override;
};

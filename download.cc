export module Download; 

import Ability; 
import Link;
import AbilityResult;

export class Download: public Ability {
    public: 
        Download(int owner);
        AbilityResult activate(Link* target) override;
        const char* getName() const override;
};

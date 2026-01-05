export module Ability;

import Link;
import Square; 
import AbilityResult;

export class Ability {
    protected: 
        bool used = false; 
        int owner = 0; //1 or 2;
        void markUsed(); 
    public:
        Ability(int owner);
        virtual ~Ability() = default;
        
        //method to activate an ability (will default return a fail if not overridden)
        virtual AbilityResult activate();

        //method to activate an ability that targets a Link
        virtual AbilityResult activate(Link* target);

        //method to activate an ability that targets a Square
        virtual AbilityResult activate(Square* target);

        //method to activate an ability that targets two Links
        virtual AbilityResult activate(Link* link1, Link* link2);

        //getter for the ability name
        virtual const char* getName() const = 0;

        //getter for used
        bool isUsed() const; 

        //getter for owner
        int getOwner() const; 
};

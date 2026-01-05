export module Player; 

import <map>;
import <memory>;
import <string>;
import <vector>;
import <iostream>;
import Ability; 
import Enums; 
import Link;

export class Player {
    const int playerNum; //1 or 2
    std::vector<std::unique_ptr<Link>> allLinks;
    std::vector<Link*> downloadedLinks; 
    std::vector<std::unique_ptr<Ability>> abilities;
    std::map<char, std::string> linkMap; 
    std::map<char, std::string> knownOpponentLinks; 

    int downloadedData = 0;
    int downloadedVirus = 0;
    int abilitiesLeft = 5; //every player starts with 5 ability uses

    public: 
        Player(int playerNum);
        
        //disable copy semantics
        Player(const Player& other) = delete;
        Player& operator=(const Player& other) = delete;

        ~Player() = default; 

        //method to download a link, updating player's stats accordingly
        void downloadLink(Link* link); 

        //decrements abilitiesLeft
        void decrementAbilityCount(); 

        //method to check if player has won 
        bool hasWon() const;

        //method to check if player has lost
        bool hasLost() const; 
        
        //method to reveal an opponent's link
        void revealOpponentLink(char c, int strength, LinkType type);

        //method to retrieve info about an opponent link
        std::string getOpponentLinkInfo(char c) const;

        //method to check if player knows info about an opponent link
        bool knowsOpponentLink(char c) const;

        //getter for player number (1 or 2)
        int getPlayerNum() const;

        //getter for total data downloaded
        int getDataDownloaded() const;

        //getter for total viruses downloaded
        int getVirusDownloaded() const;

        //getter for abilities left to use
        int getAbilitiesLeft() const;

        //getter for total links downloaded (may need for display purposes)
        int getTotalDownloaded() const;

        //getter for Link by its key in player's LinkMap, returns nullptr if not found
        Link* getLinkByKey(char c) const;

        //updating the LinkMap
        void updateLinkMap(char c);

        //getter for LinkMap
        std::map<char, std::string>& getLinkMap();

        //getter for opponent linkMap
        std::map<char, std::string>& getOpponentLinkMap(); 

        //getter for all Links
        std::vector<std::unique_ptr<Link>>& getAllLinks();

        //getter for abilities
        std::vector<std::unique_ptr<Ability>>& getAbilities();

        //method to display abilities to the console 
        void displayAbilities(); 

        //method to display a player's current stats
        friend std::ostream& operator<<(std::ostream& out, const Player& player); 
};

export std::ostream& operator<<(std::ostream& out, const Player& player);

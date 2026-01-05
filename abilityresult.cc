export module AbilityResult;

import Link;
import Square;

export struct AbilityResult {
    bool success = false; 
    bool linkScanned = false; 
    bool linkPolarized = false;
    bool linkDownloaded = false; 
    bool linkBoosted = false; 
    bool linkDiagonalized = false; 
    bool linksSwapped = false;
    bool squareFirewalled = false;
    bool squareBarriered = false; 
    Square* squareSelected = nullptr; 
    Link* linkSelected = nullptr;
    Link* linkToSwap = nullptr; //only needed for swap
    int playerAffected = -1;

    static AbilityResult failure();
    static AbilityResult download(Link* link, int player);
    static AbilityResult linkBoost(Link* link, int player);
    static AbilityResult firewall(Square* square);
    static AbilityResult barrier(Square* square);
    static AbilityResult scan(Link* link);
    static AbilityResult diagonal(Link* link, int player);
    static AbilityResult polarize(Link* link);
    static AbilityResult swap(Link* link1, Link* link2, int player);
};

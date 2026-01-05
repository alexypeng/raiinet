export module MoveResult;

import <string>;
import Link;

//struct to organize data of a move
export struct MoveResult {
    bool success = false; 
    bool linksBattled = false; 
    bool linkDownloaded = false; 
    bool movedToServerPort = false; 
    bool movedToFirewall = false; 
    int firewallOwner = -1; 
    bool movedOffOpponentEdge = false; 
    Link* winner = nullptr; 
    Link* loser = nullptr; 
    int downloadedBy = -1;
    std::string msg = "";
};

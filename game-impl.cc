module Game; 

import <memory>;
import <string>;
import <vector>;
import <map>;
import <iostream>;
import <sstream>;
import Player;
import Link;
import Ability;  
import Board; 
import Enums; 
import Square;
import LinkBoost; 
import Firewall; 
import Download; 
import Scan; 
import Polarize; 
import Diagonal;
import Barrier;
import Posn; 
import Swap;

using std::cin, std::cin, std::cout, std::endl;

//for simplicity, p1 will go first.
Game::Game() : 
    p1{std::make_unique<Player>(1)}, 
    p2{std::make_unique<Player>(2)}, 
    currPlayer{p1.get()}, 
    otherPlayer{p2.get()},
    gameOver{false} 
    {}

void Game::initGame(int argc, char* args[]){
    cout << "Welcome to RAIInet! Download 4 data links to win. But be careful! You lose if you download 4 viruses!" << endl;
    cout << "Each player will start off with 8 links. 4 data links and 4 viruses." << endl;
    cout << "You can choose to use an ability once per turn, but you only get five abilities, so be smart!" << endl;
    std::string p1Links = "V1V2V3V4D1D2D3D4";
    std::string p2Links = "V1V2V3V4D1D2D3D4";
    std::string p1Abilities = "LFDSP";
    std::string p2Abilities = "LFDSP";

    for (int i = 1; i < argc; i++) {
        std::string arg = args[i];
        if (arg == "-ability1" && i + 1 < argc && validAbilityArg(args[i+1])) {
            p1Abilities = args[i+1];
        } else if (arg == "-ability2" && i + 1 < argc && validAbilityArg(args[i+1])) {
            p2Abilities = args[i+1];
        } else if (arg == "-link1" && i + 1 < argc && validLinkArg(args[i+1])) {
            p1Links = args[i+1];
        } else if (arg == "-link2" && i + 1 < argc && validLinkArg(args[i+1])){
            p2Links = args[i+1];
        } else if (arg == "graphics") {
            graphics = true; 
        }
    }
    initPlayers(p1Links, p2Links, p1Abilities, p2Abilities);
}

bool Game::validAbilityArg(const std::string& arg) {
    if (arg.length() != 5) return false;

    const std::string allowed = "LFDSPBIW";

    std::map<char, int> abilityCount; 

    for (char c : arg) {
        if (allowed.find(c) == std::string::npos)
            return false;
        abilityCount[c]++;
        if (abilityCount[c] > 2) return false;
    }
    return true;
}

bool Game::validLinkArg(const std::string& arg) {
    if (arg.length() != 16) return false;

    bool viruses[4] = {false};
    bool data[4] = {false};

    for (int i = 0; i < 16; i += 2) {

        char type = arg[i];
        int strength = arg[i+1] - '0';

        // type must be V or D
        if (type != 'V' && type != 'D') return false;

        // strength must be 1–4
        if (strength < 1 || strength > 4) return false;

        // mark presence
        if (type == 'V')
            viruses[strength - 1] = true;
        else
            data[strength - 1] = true;
    }

    // must contain V1–V4 and D1–D4
    for (int i = 0; i < 4; i++) {
        if (!viruses[i] || !data[i])
            return false;
    }

    return true;
}


void Game::initPlayers(const std::string p1Links, const std::string p2Links, const std::string p1Abilities, const std::string p2Abilities) {
    initLinks(p1.get(), p1Links);
    initLinks(p2.get(), p2Links);
    initAbilities(p1.get(), p1Abilities);
    initAbilities(p2.get(), p2Abilities);

    notifyObservers();
}

void Game::initLinks(Player* p, const std::string& linkOrder) {
    //initialize player's links based on linkOrder string
    std::map<char, std::string>& linkMap = p->getLinkMap();
    std::vector<std::unique_ptr<Link>>& allLinks = p->getAllLinks();
    for (int i = 0; i < 16; i+= 2) {
        char alias = (p->getPlayerNum() == 1) ? 'a' + (i/2): 'A' + (i/2); //assign alias based on player number
        allLinks.emplace_back(std::make_unique<Link>(
            alias,
            (linkOrder[i] == 'D') ? LinkType::DATA : LinkType::VIRUS,
            linkOrder[i+1] - '0',
            Posn{-1, -1},
            p->getPlayerNum()
        ));
        linkMap[alias] = std::string(1, linkOrder[i]) + std::string(1, linkOrder[i+1]); //map alias to link pointer
    }
    //placing links on board
    if (p->getPlayerNum() == 1) {
        //place p1's links on row 7
        for (int j = 0; j < static_cast<int>(allLinks.size()); j++) {
            if (j == 3) {
                board.placeLink(allLinks[j].get(), Posn{6, 3});
                continue;
            }
            if (j == 4) {
                board.placeLink(allLinks[j].get(), Posn{6, 4});
                continue;
            }
            board.placeLink(allLinks[j].get(), Posn{7, j});
        }
    } else {
        //place p2's links on row 0
        for (int j = 0; j < static_cast<int>(allLinks.size()); j++) {
            if (j == 3) {
                board.placeLink(allLinks[j].get(), Posn{1, 3});
                continue;
            }
            if (j == 4) {
                board.placeLink(allLinks[j].get(), Posn{1, 4});
                continue;
            }
            board.placeLink(allLinks[j].get(), Posn{0, j});
        }
    }
}

void Game::initAbilities(Player* p, const std::string& abilityOrder) {
    std::vector<std::unique_ptr<Ability>>& abilities = p->getAbilities();
    for (int i = 0; i < 5; i++) {
        char abilityChar = abilityOrder[i];
        switch (abilityChar) {
            case 'L':
                abilities.emplace_back(std::make_unique<LinkBoost>(p->getPlayerNum()));
                break;
            case 'F':
                abilities.emplace_back(std::make_unique<Firewall>(p->getPlayerNum()));
                break;
            case 'D':
                abilities.emplace_back(std::make_unique<Download>(p->getPlayerNum()));
                break;
            case 'S':
                abilities.emplace_back(std::make_unique<Scan>(p->getPlayerNum()));
                break;
            case 'P':
                abilities.emplace_back(std::make_unique<Polarize>(p->getPlayerNum()));
                break;
            case 'I': //Diagonal
                abilities.emplace_back(std::make_unique<Diagonal>(p->getPlayerNum()));
                break;
            case 'B': //Barrier
                abilities.emplace_back(std::make_unique<Barrier>(p->getPlayerNum()));
                break;
            case 'W': //Swap
                abilities.emplace_back(std::make_unique<Swap>(p->getPlayerNum()));
                break;
            default:
                // Handle invalid ability character if necessary
                break;
        }
    }
}

void Game::switchTurn() {
    if (currPlayer == p1.get()) {
        currPlayer = p2.get();
        otherPlayer = p1.get();
    } else {
        currPlayer = p1.get();
        otherPlayer = p2.get();
    }
    abilityPlayed = false; 
    notifyObservers();
}

void Game::checkWinCondition() {
    if (currPlayer->hasWon()) {
        gameOver = true;
        notifyObservers();
        //announce winner
        cout << "Game over! Player " << currPlayer->getPlayerNum() << " has won!" << endl;
    } else if (currPlayer->hasLost()) {
        gameOver = true;
        notifyObservers();
        cout << "Game over! Player " << otherPlayer->getPlayerNum() << " has won!" << endl;
        //announce loser
    }
}

Player* Game::getCurrentPlayer() const {
    return currPlayer;
}

Player* Game::getOpponent() const {
    return otherPlayer;
}

Board* Game::getBoard() {
    return &board; 
}

bool Game::isGameOver() {
    return gameOver;
}


MoveResult Game::playMove(char c, Direction dir, Direction dir2) {
    MoveResult res; //default initialized to false
    if (!std::isalpha(c)) {
        return res; // Invalid link character
    }
    Link* linkToMove = currPlayer->getLinkByKey(c);
    if (!linkToMove) return res;
    if (dir != Direction::UP && dir != Direction::DOWN && dir != Direction::LEFT && dir != Direction::RIGHT) {
        return res;
    }
    if (dir2 != Direction::NONE && !linkToMove->canMoveDiagonally()) return res;
    if (!currentPlayerOwnsLink(c)) {
        cout << "Not current player link" << endl;
        return res; // Link does not belong to current player
    }
    Posn linkPos = board.findLink(c);
    if (linkPos == Posn{-1, -1}) {
        cout << "Link not found on board" << endl;
        return res; // Link not found on board
    }
    Posn newPos = linkPos.move(currPlayer->getPlayerNum(), dir, linkToMove->isLinkBoosted());
    if (dir2 != Direction::NONE) {
        newPos = newPos.move(currPlayer->getPlayerNum(), dir2, linkToMove->isLinkBoosted());
    }

    res = board.moveLink(linkPos, newPos);
    cout << res.msg << endl;
    if (!res.success) return res; 

    //check results, change state based on res
    if (res.linksBattled) {
        //winner download loser, reveal both links to both players
        Link* winner = res.winner;
        Link* loser = res.loser;
        if (res.winner->getOwner() == 1) {
            p1.get()->revealOpponentLink(loser->getAlias(), loser->getStrength(), loser->getType());
            p2.get()->revealOpponentLink(winner->getAlias(), winner->getStrength(), winner->getType());
            p1.get()->downloadLink(loser);
        } else {
            p1.get()->revealOpponentLink(winner->getAlias(), winner->getStrength(), winner->getType());
            p2.get()->revealOpponentLink(loser->getAlias(), loser->getStrength(), loser->getType());
            p2.get()->downloadLink(loser);
        }
        checkWinCondition();
    } 
    if (res.movedToFirewall) {
        cout << "Player " << currPlayer->getPlayerNum() << " Moved to a firewall!" << endl;
        if (res.firewallOwner != currPlayer->getPlayerNum()) {
            otherPlayer->revealOpponentLink(linkToMove->getAlias(), linkToMove->getStrength(), linkToMove->getType());
        }
        if (res.linkDownloaded) {
            cout << "Downloaded by: Player " << res.downloadedBy << endl;
            if (res.downloadedBy == 1) p1.get()->downloadLink(linkToMove);
            else p2.get()->downloadLink(linkToMove);
            board.getSquare(newPos)->removeLink();
            checkWinCondition();
        }
    }
    if (res.movedOffOpponentEdge || res.movedToServerPort) {
        if (res.downloadedBy == 1) p1.get()->downloadLink(linkToMove);
        else p2.get()->downloadLink(linkToMove);
        if (res.movedToServerPort) {
            board.getSquare(newPos)->removeLink();
        }
        checkWinCondition();
    }
    checkWinCondition();
    switchTurn();
    return res; 
}

//ability <N> <Square>/<Link> #<Link2>
AbilityResult Game::playAbility(int index, const std::string& targetInfo) {
    if (abilityPlayed) return AbilityResult::failure();
    if (index < 1 || index > 5) return AbilityResult::failure();
    cout << "Player " << currPlayer->getPlayerNum() << " tries to play an Ability." << endl;
    Ability* ability = currPlayer->getAbilities()[index - 1].get();
    if (ability->isUsed()) return AbilityResult::failure();
    
    const std::string name = ability->getName();
    AbilityResult res;
    
    if (name == "Link Boost") {
        Link* link = parseLink(targetInfo[0]);
        if (link) res = ability->activate(link);
    } else if (name == "Scan" || name == "Download" || name == "Polarize" || name == "Diagonal") {
        Link* link = parseLink(targetInfo[0]);
        if (link) res = ability->activate(link);
    } else if (name == "Firewall" || name == "Barrier") {
        Square* square = parseSquare(targetInfo);
        if (square) res = ability->activate(square);
    } else if (name == "Swap") {
        auto [link1, link2] = parseTwoLinks(targetInfo);
        cout << "Player " << currPlayer->getPlayerNum() << " tries to Swap " << link1->getAlias() << " and " << link2->getAlias() << "." << endl;
        if (link1 && link2) res = ability->activate(link1, link2);
    }
    
    if (res.success) {
        cout << "Ability succeeded!" << endl;
        abilityPlayed = true;
        currPlayer->decrementAbilityCount();
        if (res.linkScanned) {
            cout << res.linkSelected->getAlias() << " is being Scanned! It's info is now revealed to all players." << endl;
            res.linkSelected->reveal();
            if (res.linkSelected->getOwner() == 1) {
                p2.get()->revealOpponentLink(res.linkSelected->getAlias(), res.linkSelected->getStrength(), res.linkSelected->getType());
            } else {
                p1.get()->revealOpponentLink(res.linkSelected->getAlias(), res.linkSelected->getStrength(), res.linkSelected->getType());
            }
        }
        if (res.linkPolarized) {
            cout << "Player " << res.linkSelected->getOwner() << " is polarizing " << res.linkSelected->getAlias() << "!" << endl;
            res.linkSelected->polarize();
            Player* owner = (res.linkSelected->getOwner() == 1) ? p1.get() : p2.get();
            char alias = res.linkSelected->getAlias();
            char typeChar = (res.linkSelected->getType() == LinkType::DATA) ? 'D' : 'V';
            int strength = res.linkSelected->getStrength();
            owner->getLinkMap()[alias] = std::string(1, typeChar) + std::to_string(strength);
        }
        if (res.linkDownloaded) {
            cout << "Player " << res.playerAffected << " is downloading " << res.linkSelected->getAlias() << "!" << endl;
            if (res.playerAffected == 1) {
                p1.get()->downloadLink(res.linkSelected);
            } else {
                p2.get()->downloadLink(res.linkSelected);
            }
            board.getSquare(res.linkSelected->getPosn())->removeLink();
            checkWinCondition();
        }
        if (res.linkBoosted) {
            res.linkSelected->boostLink();
            cout << "Player " << currPlayer->getPlayerNum() << " boosted Link " << res.linkSelected->getAlias() << "!" << endl;
        }
        if (res.linkDiagonalized) {
            res.linkSelected->allowDiagonalMovement();
            cout << "Player " << currPlayer->getPlayerNum() << " allowed " << res.linkSelected->getAlias() << " to move diagonally!" << endl;
        }
        if (res.linksSwapped) {
            Posn pos1 = res.linkSelected->getPosn();
            Posn pos2 = res.linkToSwap->getPosn();
            Link* tmp = board.getSquare(pos1)->removeLink();
            Link* tmp2 = board.getSquare(pos2)->removeLink();
            board.placeLink(tmp, pos2);
            board.placeLink(tmp2, pos1);
            cout << "Player " << currPlayer->getPlayerNum() << " swapped the places of two links!" << endl;
        }
        if (res.squareFirewalled) {
            res.squareSelected->setFirewall(currPlayer->getPlayerNum());
            cout << "Player " << currPlayer->getPlayerNum() << " set a firewall!" << endl;
        }
        if (res.squareBarriered) {
            res.squareSelected->setBarrier();
            cout << "Player " << currPlayer->getPlayerNum() << " set a barrier!" << endl;
        }
    }
    notifyObservers();
    return res;
}

// Parse single link: "a" or "A"
Link* Game::parseLink(char info) {
    Link* l = currPlayer->getLinkByKey(info);
    if (!l) l = otherPlayer->getLinkByKey(info);
    return l; 
}

// Parse square coordinates: "3,4" or "3 4"
Square* Game::parseSquare(const std::string& info) {
    std::istringstream iss{info};
    int row, col;
    if (iss >> row >> col) {
        return board.getSquare(row, col);
    }
    return nullptr;
}

// Parse two links: "a B"
std::pair<Link*, Link*> Game::parseTwoLinks(const std::string& info) {
    std::istringstream iss{info};
    char c1, c2;
    if (iss >> c1 >> c2) {
        return {parseLink(c1), parseLink(c2)};
    }
    return {nullptr, nullptr};
}

bool Game::currentPlayerOwnsLink(char c) const {
    if (currPlayer->getPlayerNum() == 1) {
        return c >= 'a' && c <= 'h';
    } else {
        return c >= 'A' && c <= 'H';
    }
}

import <iostream>;
import <sstream>;
import <string>;
import <fstream>;

import Link;
import Posn;
import Enums;
import Board; 
import Square;
import Player; 
import MoveResult;
import AbilityResult;
import Game;
import TextDisplay; 
import GraphicDisplay;

using namespace std;

// Returns false if quit was requested, true otherwise
bool processCommand(const string& cmd, Game& g, TextDisplay& td) {
    istringstream iss{cmd};
    string tkn;
    iss >> tkn; 
    if (!iss) return true; 

    if (tkn == "move") {
        char c;
        string dir;
        iss >> c >> dir;
        Direction d; 
        if (dir == "up") {
            d = Direction::UP;
        } else if (dir == "down") {
            d = Direction::DOWN;
        } else if (dir == "left") {
            d = Direction::LEFT;
        } else if (dir == "right") {
            d = Direction::RIGHT; 
        } else {
            return true;
        }
        Direction d2 = Direction::NONE; //if you can move diagonally
        string dir2;
        if (iss >> dir2) {
            if (dir2 == "up") {
                d2 = Direction::UP;
            } else if (dir2 == "down") {
                d2 = Direction::DOWN;
            } else if (dir2 == "left") {
                d2 = Direction::LEFT;
            } else if (dir2 == "right") {
                d2 = Direction::RIGHT;
            } else {
                return true;
            }
        }

        g.playMove(c, d, d2);
    } else if (tkn == "abilities") {
        cout << endl;
        g.getCurrentPlayer()->displayAbilities();
        cout << endl;
    } else if (tkn == "ability") {
        int index;
        iss >> index; 
        if (!iss) return true; 
        string targetInfo;
        getline(iss, targetInfo); 
        size_t start = targetInfo.find_first_not_of(" \t");
        if (start != string::npos) {
            targetInfo = targetInfo.substr(start);
        }
        AbilityResult res = g.playAbility(index, targetInfo);
        if (!res.success) {
            cerr << "Ability failed." << endl;
        }
    } else if (tkn == "board") {
        cout << endl;
        cout << td << endl;
        cout << endl;
    } else if (tkn == "sequence") {
        string filename;
        iss >> filename;
        if (!iss) return true;
        ifstream file{filename};
        if (!file) {
            cerr << "Cannot open file: " << filename << endl;
            return true;
        }
        string filecmd;
        while (getline(file, filecmd) && !g.isGameOver()) {
            if (!processCommand(filecmd, g, td)) return false;
        }
    } else if (tkn == "quit") {
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    Game g;
    TextDisplay td = TextDisplay(&g);
    GraphicDisplay* gd = nullptr;

    for (int i = 1; i < argc; ++i) {
        if(string(argv[i]) == "-graphics") {
            gd = new GraphicDisplay(&g);
            break;
        }
    }

    g.initGame(argc, argv);
    string cmd; 
    while (!g.isGameOver()) {
        if (getline(cin, cmd)) {
            if (!processCommand(cmd, g, td)) break;
        }
    }
    return 0;
}

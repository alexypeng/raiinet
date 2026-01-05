module TextDisplay;

import <iostream>;
import <map>;
import Player;
import Board;
import Square;
import Link;

using namespace std;

TextDisplay::TextDisplay(Game* g):game{g}{}
TextDisplay::~TextDisplay(){}

void TextDisplay::printBoard(ostream& out) {
    bool reverse = game->getCurrentPlayer()->getPlayerNum() == 2;

    out << "========" << std::endl;
    for (int i = 0; i < Board::getDimensions(); i++) {
        int row = reverse ? (7 - i) : i;
        for (int j = 0; j < Board::getDimensions(); j++) {
            int col = reverse ? (7 - j) : j;
            Square* square = game->getBoard()->getSquare(row, col);
            //can modify symbols after further implementation
            if (!square->isEmpty()) {
                Link* link = square->getLink();
                out << link->getAlias(); 
            } else if (square->isServerPort()) {
                out << "S"; //can replace if needed
            } else if (square->isFirewall()) {
                if (square->getFirewallOwner() == 1) {
                    out << "m"; //player 1 firewall
                } else {
                    out << "w"; //player 2 firewall
                }
            } else if (square->isBarrier()) {
                out << "X"; //can replace if needed
            } else {
                out << ".";
            }
        }
        out << std::endl;
    }
    out << "========" << std::endl;
}

void TextDisplay::print(ostream& out) {
    Player* currentPlayer = game->getCurrentPlayer();
    Player* opponent = game->getOpponent();

    out << "Player " << currentPlayer->getPlayerNum() << ":" << endl;
    out << "Downloaded: " << currentPlayer->getDataDownloaded() << "D, " << currentPlayer->getVirusDownloaded() << "V" << endl;
    out << "Abilities: " << currentPlayer->getAbilitiesLeft() << endl;
    int counter = 0;
    for (const auto& [key, value] : currentPlayer->getLinkMap()) {
        out << key << ": " << value;
        ++counter;
        if (counter % 4 == 0) out << endl;
        else out << "\t";
    }

    printBoard(out);

    out << "Player " << opponent->getPlayerNum() << ":" << endl;
    out << "Downloaded: " << opponent->getDataDownloaded() << "D, " << opponent->getVirusDownloaded() << "V" << endl;
    out << "Abilities: " << opponent->getAbilitiesLeft() << endl;
    counter = 0;
    char oppAlias = (currentPlayer->getPlayerNum() == 1 ? 'A' : 'a');
    map<char, string>& oppLinkMap = currentPlayer->getOpponentLinkMap();
    for (int i = 0; i < 8; i++) {
        char alias = oppAlias + i; 
        out << alias << ": ";
        if (!currentPlayer->knowsOpponentLink(alias)) out << "?";
        else out << oppLinkMap[alias];
        if (i == 3) out << endl;
        else out << "\t";
    }
}

std::ostream& operator<<(std::ostream& out, TextDisplay& td) {
    td.print(out);
    return out;
}

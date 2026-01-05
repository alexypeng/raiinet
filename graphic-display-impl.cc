module GraphicDisplay;

import <iostream>;
import <memory>;
import Board;
import Square;
import Link;
import Player;
import Enums;

GraphicDisplay::GraphicDisplay(Game* game)
    : CELLSIZE{70}, 
      OFFSETX{35}, 
      OFFSETY{100}, 
      BOARDSIZE{Board::getDimensions()}, 
      game{game},
      xw{std::make_unique<Xwindow>(BOARDSIZE * CELLSIZE + 2 * OFFSETX,
                                     BOARDSIZE * CELLSIZE + 2 * OFFSETY)} {
        game->attach(this);
    }

GraphicDisplay::~GraphicDisplay() {
    game->detach(this);
}

void GraphicDisplay::notify() {
    render();
}

void GraphicDisplay::render() {
    xw->fillRectangle(0, 0,  BOARDSIZE * CELLSIZE + 2 * OFFSETX,
                      BOARDSIZE * CELLSIZE + 2 * OFFSETY, Xwindow::White);
    drawPlayerInfo();
    drawGrid();
    xw->flush();
}

void GraphicDisplay::drawGrid() {
    bool reverse = game->getCurrentPlayer()->getPlayerNum() == 2;

    for (int i = 0; i < Board::getDimensions(); i++) {
        int row = reverse ? (7 - i) : i;
        for (int j = 0; j < Board::getDimensions(); j++) {
            int col = reverse ? (7 - j) : j;
            drawCell(row, col);
        }
    }
}

int GraphicDisplay::getCellColour(Square *sq) const {
    if(sq->isBarrier()) return Xwindow::Brown;
    if (sq->isFirewall()) {
        int owner = sq->getFirewallOwner();
        return (owner == game->getCurrentPlayer()->getPlayerNum()) ? Xwindow::Cyan : Xwindow::Orange;
    }
    if (sq->isServerPort()) {
        int owner = sq->getServerPortOwner();
        return (owner == game->getCurrentPlayer()->getPlayerNum()) ? Xwindow::Blue : Xwindow::Magenta;
    }
    return Xwindow::White;
}

int GraphicDisplay::getLinkColour(Link *link) const {
    if(game->getCurrentPlayer()->getPlayerNum() == link->getOwner()) {
        if (link->getType() == LinkType::DATA) {
            return Xwindow::Green;
        } else {
            return Xwindow::Red;
        }
    }

    if (game->getCurrentPlayer()->getOpponentLinkMap().count(link->getAlias())) {
        if (link->getType() == LinkType::DATA) {
            return Xwindow::Green;
        } else {
            return Xwindow::Red;
        }
    }

    return Xwindow::Black;
}

void GraphicDisplay::drawPlayerInfo() {
    Player* currentPlayer = game->getCurrentPlayer();
    Player* opponent = game->getOpponent();
    
    // Determine which player is which for display
    Player* p1 = (currentPlayer->getPlayerNum() == 1) ? currentPlayer : opponent;
    Player* p2 = (currentPlayer->getPlayerNum() == 1) ? opponent : currentPlayer;
    
    int textX = 45;
    int lineHeight = 25;
    int p1Y = 30;
    int p2Y = OFFSETY + BOARDSIZE * CELLSIZE + 30;
    
    // Player 1 info
    xw->drawString(textX, p1Y, "Player 1:");
    xw->drawString(textX, p1Y + lineHeight, 
                   "Downloaded: " + 
                   std::to_string(p1->getDataDownloaded()) + "D, " + 
                   std::to_string(p1->getVirusDownloaded()) + "V");
    xw->drawString(textX, p1Y + 2 * lineHeight, 
                   "Abilities: " + std::to_string(p1->getAbilitiesLeft()));
    
    // Player 2 info
    xw->drawString(textX, p2Y, "Player 2:");
    xw->drawString(textX, p2Y + lineHeight, 
                   "Downloaded: " + 
                   std::to_string(p2->getDataDownloaded()) + "D, " + 
                   std::to_string(p2->getVirusDownloaded()) + "V");
    xw->drawString(textX, p2Y + 2 * lineHeight, 
                   "Abilities: " + std::to_string(p2->getAbilitiesLeft()));
}

void GraphicDisplay::drawCell(int row, int col) {
    Board *board = game->getBoard();
    Square *square = board->getSquare(row, col);

    if (!square) return;

    bool reverse = game->getCurrentPlayer()->getPlayerNum() == 2;

    int visualRow = reverse ? (7 - row) : row;
    int visualCol = reverse ? (7 - col) : col;

    int x = OFFSETX + visualCol * CELLSIZE;
    int y = OFFSETY + visualRow * CELLSIZE;

    int bgColour = getCellColour(square);
    xw->fillRectangle(x, y, CELLSIZE, CELLSIZE, bgColour);

    int borderWidth = 2;
    xw->fillRectangle(x, y, CELLSIZE, borderWidth, Xwindow::Black);  // Top
    xw->fillRectangle(x, y + CELLSIZE - borderWidth, CELLSIZE, borderWidth, Xwindow::Black);  // Bottom
    xw->fillRectangle(x, y, borderWidth, CELLSIZE, Xwindow::Black);  // Left
    xw->fillRectangle(x + CELLSIZE - borderWidth, y, borderWidth, CELLSIZE, Xwindow::Black);  // Right

    // Draw link if present
    Link* link = square->getLink();
    if (link) {
        Player* currentPlayer = game->getCurrentPlayer();
        char alias = link->getAlias();
        int linkOwner = link->getOwner();
        int textColour = getLinkColour(link);
        
        std::string displayText;
        
        // If it's my own link or I know the opponent's link, show strength
        if (linkOwner == currentPlayer->getPlayerNum() ||
            currentPlayer->getOpponentLinkMap().count(alias)) {
            displayText = std::to_string(link->getStrength());
        } else {
            // Unknown opponent link - just show alias
            displayText = std::string(1, alias);
        }

        // Draw colored background for text
        int rectSize = CELLSIZE / 3;
        int rectX = x + CELLSIZE / 2 - rectSize / 2;
        int rectY = y + CELLSIZE / 2 - rectSize / 2;
        xw->fillRectangle(rectX, rectY, rectSize, rectSize, textColour);

        // Draw text
        int textX = x + CELLSIZE / 2 - 2;
        int textY = y + CELLSIZE / 2 + 5;
        xw->drawString(textX, textY, displayText);
    }
}

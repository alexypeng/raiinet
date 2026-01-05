export module GraphicDisplay;

import IObserver;
import Game;
import xwindow;
import Link;
import Square;
import <memory>;

export class GraphicDisplay : public IObserver {
    const int CELLSIZE;
    const int OFFSETX;
    const int OFFSETY;
    const int BOARDSIZE;
    Game* game;
    std::unique_ptr<Xwindow> xw;

    void drawCell(int row, int col);
    void drawGrid();
    void drawPlayerInfo();
    int getCellColour(Square *sq) const;
    int getLinkColour(Link *link) const;

public:
    GraphicDisplay(Game *game);
    ~GraphicDisplay();
    void notify() override;
    void render();
};

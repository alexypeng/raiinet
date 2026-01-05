export module TextDisplay;

import Game;
import <iostream>;

using namespace std;

export class TextDisplay {
    Game* game;

    void printBoard(ostream& out);
    public:
        TextDisplay(Game* game);
        ~TextDisplay();
        void print(ostream& out);
        friend ostream& operator<<(ostream& out, TextDisplay& td);
};

module;
#include <X11/Xlib.h>
export module xwindow;
import <iostream>;
import <string>;

export class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];
  Pixmap pix;
  int width, height;

 public:
  Xwindow(int width=750, int height=750);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.
  Xwindow(const Xwindow&) = delete;
  Xwindow &operator=(const Xwindow&) = delete;

  // Available colours.
  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=White);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  void flush();
};


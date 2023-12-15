#include "Bitmap.h"
#include "GameBoard.h"
#include "Movements.h"

Bitmap::Bitmap(std::vector<Triple> &b, const int &z): Item{0,0,z}, bitmap{b} {}
Bitmap::Bitmap(): Item{0,0,0} {}

Bitmap::Bitmap(int &x, int &y, int &z, char &c): Item{0,0,z}, 
  bitmap{Triple{x, y, c}} {}

ErrorCode Bitmap::draw(WINDOW *Board) {
  if (periodicMovement) {
    if (periodicMovement->getPos() != 0) {
      return periodicMovement->draw(Board);
    }
  }

  for (Triple &t: bitmap) {
    mvwaddch(Board, t.y + getY(), t.x + getX(), t.c);
  }
  return Success;
}

int Bitmap::getHeight() {
  return 0;
}

int Bitmap::getWidth() {
  return 0;
}

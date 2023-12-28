#include "Single.h"
#include "Movements.h"

ErrorCode Single::draw(WINDOW *Board) {
  init_pair(getID(), color, COLOR_BLACK);
  wattron(Board, COLOR_PAIR(getID()));
  if (periodicMovement != nullptr) {
    if (periodicMovement->getPos() != 0) {
      return periodicMovement->draw(Board);
    }
  }
  mvwaddch(Board, getY(), getX(), c);
  wattroff(Board, COLOR_PAIR(getID()));
  return Success;
}

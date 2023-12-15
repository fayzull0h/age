#include "Single.h"
#include "Movements.h"

ErrorCode Single::draw(WINDOW *Board) {
  if (periodicMovement != nullptr) {
    if (periodicMovement->getPos() != 0) {
      return periodicMovement->draw(Board);
    }
  }
  mvwaddch(Board, getY(), getX(), c);
  return Success;
}

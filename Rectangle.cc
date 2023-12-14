#include "Rectangle.h"
#include "GameBoard.h"
#include "Item.h"
#include "Movements.h"

ErrorCode Rectangle::draw(WINDOW *Board) {
  if (periodicMovement != nullptr) {
    if (periodicMovement->getPos() != 0) {
      return periodicMovement->draw(Board);
    }
  }

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      mvwaddch(Board, getY()+i, getX()+j, c);
    }
  }
  return Success;
}

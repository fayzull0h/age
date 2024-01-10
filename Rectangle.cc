#include "Rectangle.h"
#include "GameBoard.h"
#include "Item.h"
#include "Movements.h"
#include <ncurses.h>

ErrorCode Rectangle::draw(WINDOW *Board) {
  init_pair(getID(), frontColor, backColor);
  wattron(Board, COLOR_PAIR(getID()));
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
  wattroff(Board, COLOR_PAIR(getID()));
  return Success;
}

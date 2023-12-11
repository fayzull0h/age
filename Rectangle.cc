#include "Rectangle.h"
#include "PeriodicMovement.h"

ErrorCode Hollow::drawrect(WINDOW *Board) {
  int width{getWidth()}, height{getHeight()};
  char c{getChar()};
  for (int i = 0; i < width; ++i) {
    mvwaddch(Board, getY(), getX()+i, c);
    mvwaddch(Board, getY()+height-1, getX()+i, c);
  }
  for (int i = 1; i < height-1; ++i) {
    mvwaddch(Board, getY()+i, getX(), c);
    mvwaddch(Board, getY()+i, getX()+width-1, c);
  }
  return ErrorCode::Success;
}

ErrorCode Full::drawrect(WINDOW *Board) {
  wmove(Board, getY(), getX());
  int width{getWidth()}, height{getHeight()};
  char c{getChar()};
  for (int i = 0; i <= height; ++i) {
    for (int j = 0; j < width; ++j) waddch(Board, c);
    wmove(Board, getY()+i, getX());
  }
  return ErrorCode::Success;
}

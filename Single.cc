#include "Single.h"

ErrorCode Single::draw(WINDOW *Board) {
  mvwaddch(Board, getY(), getX(), c);
  return ErrorCode::Success;
}

#include "Rectangle.h"

HollowRectangle::HollowRectangle(int x, int y, int z, int height, int width, char c): Item{x, y, z},
 c{c}, height{height}, width{width} {}

FullRectangle::FullRectangle(int x, int y, int z, int height, int width, char c): Item{x, y, z},
 c{c}, height{height}, width{width} {}

ErrorCode HollowRectangle::draw(WINDOW *Board) {
  wmove(Board, getY(), getX());
  for (int i = 0; i < width; ++i) {
    mvwaddch(Board, getY(), getX()+i, c);
    mvwaddch(Board, getY()+height-1, getX()+i, c);
  }
  wmove(Board, getY()+1, getX());
  for (int i = 0; i < height - 2; ++i) {
    mvwaddch(Board, i, getX(), c);
    mvwaddch(Board, i, getX()+width-1, c);
  }
  return ErrorCode::Success;
}

ErrorCode FullRectangle::draw(WINDOW *Board) {
  wmove(Board, getY(), getX());
  for (int i = 0; i <= height; ++i) {
    for (int j = 0; j < width; ++j) waddch(Board, c);
    wmove(Board, getY()+i, getX());
  }
  return ErrorCode::Success;
}

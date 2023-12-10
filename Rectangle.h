#ifndef RECT_H
#define RECT_H

#include "Item.h"

class HollowRectangle: public Item {
  char c;
  int height, width;
 public:
  HollowRectangle(int x, int y, int z, int height, int width, char c);
  ErrorCode draw(WINDOW *Board) override;
};

class FullRectangle: public Item {
  char c;
  int x, y, z, height, width;
 public:
  FullRectangle(int x, int y, int z, int height, int width, char c);
  ErrorCode draw(WINDOW *Board) override;
};

#endif

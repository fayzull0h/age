#ifndef BITMAP_H
#define BITMAP_H

#include "Item.h"
#include "metadata.h"
#include <vector>

class GameBoard;

class Bitmap: public Item {
  std::vector<Triple> bitmap;
 public:
  Bitmap(std::vector<Triple> &b, const int &z);
  Bitmap(int &x, int &y, int &z, char &c);
  ErrorCode draw(WINDOW *Board) override;
  int getHeight() override;
  int getWidth() override;
};

#endif

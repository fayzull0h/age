#ifndef RECT_H
#define RECT_H

#include "Item.h"

class GameBoard;

class Rectangle: public Item {
  char c;
  int height, width;
 public:
  Rectangle(int x, int y, int z, int height, int width, char c, int col): 
    Item{x, y, z, col}, c{c}, height{height}, width{width} {}
  
  // Rectangle(Rectangle &r): Item{r.getID(), r.getX(), r.getY(), r.getZ(), r.color}, c{r.c},
  //   height{r.height}, width{r.width} {}

  ErrorCode draw(WINDOW *Board) override;

  int getHeight() override { return height; }
  int getWidth() override { return width; }
  ~Rectangle() {}
};

#endif

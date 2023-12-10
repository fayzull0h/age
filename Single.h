#ifndef SINGLE_H 
#define SINGLE_H

#include "Item.h"

class Single: public Item {
  char c;
 public:
  Single(int x, int y, int z, char c): Item{x, y, z}, c{c} {}
  ErrorCode draw(WINDOW *Board) override;
};

#endif

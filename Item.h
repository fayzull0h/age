#ifndef ITEM_H
#define ITEM_H

#include "metadata.h"
#include "observer.h"
#include <vector>
#include <ncurses.h>

class PeriodicMovement;

class Item: public Observer<Info, State> {
  int x, y, z;
  PeriodicMovement *movement;
 public:
  Item(int x, int y, int z);
  Item(int x, int y, int z, PeriodicMovement *pm);
  ErrorCode notify(Subject<Info, State> &whoFrom) override;
  ErrorCode setMovement(PeriodicMovement *pm);
  ErrorCode doMovement();
  virtual ErrorCode draw(WINDOW *Board) = 0;
  int getX() const; 
  int getY() const; 
  int getZ() const; 
};

#endif 

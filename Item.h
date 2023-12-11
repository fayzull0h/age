#ifndef ITEM_H
#define ITEM_H

#include "metadata.h"
#include "observer.h"
#include <vector>
#include <ncurses.h>
#include "PeriodicMovement.h"

class Item: public Observer<Info, State> {
  int x, y, z;
  PeriodicMovement movement;
 public:
  Item(int x, int y, int z);
  Item(int x, int y, int z, PeriodicMovement &pm);
  ErrorCode notify(Subject<Info, State> &whoFrom) override;
  ErrorCode setMovement(PeriodicMovement &pm);
  PeriodicMovement &getMovement();
  virtual ErrorCode doMovement() = 0;
  virtual ErrorCode draw(WINDOW *Board) = 0;
  int getX() const; 
  int getY() const; 
  int getZ() const;
  ErrorCode addX(int i);
  ErrorCode addY(int i);
  ErrorCode addZ(int i);
};

#endif 

#ifndef ITEM_H
#define ITEM_H

#include "metadata.h"
#include <vector>
#include <ncurses.h>
#include <memory>

class Movement;
class PeriodicMovement;
class GameBoard;

class Item {
  int x, y, z;
  int ticksOffScreen;
 protected:
  PeriodicMovement *periodicMovement;
  std::vector<Movement *> movements;
  std::vector<Collision *> collisions;
 public:
  Item(int x, int y, int z);
  virtual ErrorCode draw(WINDOW *Board) = 0;
  virtual int getHeight() = 0;
  virtual int getWidth() = 0;

  ErrorCode addMovement(Movement *m);
  ErrorCode doMovements(GameBoard *gb);
  ErrorCode tick(GameBoard *gb);

  int getX(); 
  int getY(); 
  int getZ();
  ErrorCode addX(int i);
  ErrorCode addY(int i);
  ErrorCode addZ(int i);
  int getTicks() const;
  ErrorCode addTick();
};

#endif 

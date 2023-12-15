#ifndef ITEM_H
#define ITEM_H

#include "metadata.h"
#include "Collision.h"
#include <vector>
#include <ncurses.h>
#include <memory>

class Movement;
class PeriodicMovement;
class GameBoard;
class GameState;

class Item {
  int x, y, z;
  int ticksOffScreen;
  int xvelocity, yvelocity;
 protected:
  PeriodicMovement *periodicMovement;
 public:
  Item(int x, int y, int z);
  virtual ErrorCode draw(WINDOW *Board) = 0;
  virtual int getHeight() = 0;
  virtual int getWidth() = 0;

  ErrorCode setMovement(Movement *m);
  ErrorCode setPeriodicMovement(PeriodicMovement *pm);

  ErrorCode tick(GameState *gs, BoardType btype);

  int getX(); 
  int getY(); 
  int getZ();
  int setX(int n) { return x = n; }
  int setY(int n) { return y = n; }
  int setZ(int n) { return z = n; }
  ErrorCode addX(int i);
  ErrorCode addY(int i);
  ErrorCode addZ(int i);
  int getXV() const { return xvelocity; }
  int getYV() const { return yvelocity; }
  int setXV(int n) { return xvelocity = 2*n; }
  int setYV(int n) { return yvelocity = n; }
  int reverseXV() { return xvelocity *= -1; }
  int reverseYV() { return yvelocity *= -1; }
  int stopXV() { return xvelocity = 0; }
  int stopYV() { return yvelocity = 0; }
  ErrorCode addTick();
};

#endif 

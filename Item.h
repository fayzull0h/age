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
  std::vector<Collision *> collisions;
 public:
  Item(int x, int y, int z);
  virtual ErrorCode draw(WINDOW *Board) = 0;
  virtual int getHeight() = 0;
  virtual int getWidth() = 0;

  ErrorCode setMovement(Movement *m);
  ErrorCode setPeriodicMovement(PeriodicMovement *pm);
  /* TO DELETE */
  // ErrorCode doMovements(GameBoard *gb);
  ErrorCode tick(GameState *gs, GameBoard *gb);

  int getX(); 
  int getY(); 
  int getZ();
  ErrorCode addX(int i);
  ErrorCode addY(int i);
  ErrorCode addZ(int i);
  int getTicks() const;
  int getXV() const { return xvelocity; }
  int getYV() const { return yvelocity; }
  int reverseXV() { return xvelocity *= -1; }
  int reverseYV() { return yvelocity *= -1; }
  int stopXV() { return xvelocity = 0; }
  int stopYV() { return yvelocity = 0; }
  ErrorCode addTick();
};

#endif 

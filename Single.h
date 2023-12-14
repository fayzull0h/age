#ifndef SINGLE_H 
#define SINGLE_H

#include "Item.h"

class GameBoard;

class Single: public Item {
  char c;
 public:
  Single(int x, int y, int z, char c): Item{x, y, z}, c{c} {}
  Single(Single &s): Item{s.getX(), s.getY(), s.getZ()}, c{s.c} {}
  ErrorCode draw(WINDOW *Board) override;
  int getHeight() override { return 1; }
  int getWidth() override { return 1; }
};

#endif

/* Tutorial notes */ 
/*
class GameState {
  vector<Item> items;
  vector<Collision> collisions;
  ...
}

GameState game;
GameState win;

give some control of game loop to client
- such as allowing the client to specify methods to update certain things

when collision:
  - could throw exception to say win State
  - have velocity field for items
  - don't really need to implement collision for bitmap'
*/

#ifndef GAMESTATE_H
#define GAMESTATE_H

class Item;
class Collision;
class Status;

#include <cstddef>
#include <vector>
#include "metadata.h"

class GameState {
 protected:
  std::vector<Status> stats;
  std::vector<Item *> items;
  std::vector<Collision *> collisions;
  Item *player;
 public:
  GameState(): player{nullptr} {}
  ErrorCode addStat(const Status &s);
  ErrorCode addItem(Item *item);
  ErrorCode addPlayer(Item *p);
  ErrorCode addCollision(Collision *c);

  Item *getPlayer() { return player; }
  
  ErrorCode deleteItem(Item *it);

  const std::vector<Status> *getStats() const { return &stats; } 
  const std::vector<Item *> *getItems() { return &items; }
  std::vector<Collision *> *getCollisions() { return &collisions; }

  virtual ErrorCode tick(BoardType btype) = 0;
 
  ~GameState() { if (player) player = nullptr; }
  friend class Engine;
};

#endif

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <cstddef>
#include <vector>
#include "metadata.h"

class Item;

class GameState {
  StateType state;
  std::vector<Status> stats;
  std::vector<Item *> items;
  Item *player;
 public:
  GameState(): state{NoChange}, player{nullptr} {}
  ErrorCode addStat(const Status &s);
  StateType getState();
  ErrorCode addItem(Item *item);
  ErrorCode addPlayer(Item *p);

  Item *getPlayer() { return player; }

  const std::vector<Status> *getStats() const;
  const std::vector<Item *> *getItems() { return &items; }
  ~GameState() { if (player) player = nullptr; }
  friend class Engine;
};

#endif

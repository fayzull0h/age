#ifndef ENGINE_H
#define ENGINE_H

#include "subject.h"
#include "observer.h"
#include "metadata.h"
#include "Item.h"

class GameBoard;

class Engine: public Subject<Info, State> {
  Status stat1, stat2, stat3;
  size_t statcount;
  std::vector<Item *> items;
  GameBoard *gb; 
  State state;
 public:
  Engine();
  ErrorCode go();
  ErrorCode addStat(const Status &s); 
  State getState() const;
  ErrorCode addGameBoard(GameBoard *b);
  ErrorCode addItem(Item *item);
  std::vector<Status> getStats() const;
};

#endif

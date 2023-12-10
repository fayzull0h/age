#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "observer.h"
#include "subject.h"
#include <ncurses.h>
#include "metadata.h"
#include <vector>

class Item;
class Engine;

class GameBoard: public Subject<Info, State>, public Observer<Info, State> {
  WINDOW *Board;
  std::vector<Item *> items;
 public:
  GameBoard();
  ErrorCode addItem(Item *it);
  ErrorCode notify(Subject<Info, State> &whoFrom) override;
  ErrorCode drawBoard(Engine *eng);
  WINDOW * getBoard() const;
  ~GameBoard();
};

#endif 

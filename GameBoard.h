#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <ncurses.h>
#include "metadata.h"
#include <vector>

class Item;
class Engine;
class GameState;

class GameBoard {
  WINDOW *Board;
  ErrorCode init();
 public:
  const BoardType boardtype;
  GameBoard(BoardType b);
  ErrorCode drawState(GameState *gs);
  WINDOW *getBoard() const;
  ErrorCode drawWin();
  ErrorCode drawLose();
  ErrorCode resize(int rows, int cols);
  ~GameBoard();
  friend class Engine;
};

#endif

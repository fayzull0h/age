#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <ncurses.h>
#include "metadata.h"
#include <vector>

class Item;
class Engine;
class GameState;

enum BoardType { Solid, View };

class GameBoard {
  WINDOW *Board;
  ErrorCode init();
 public:
  const BoardType boardtype;
  GameBoard(BoardType b);
  ErrorCode drawState(GameState *gs);
  WINDOW *getBoard() const;
  ErrorCode drawWin();
  ~GameBoard();
  friend class Engine;
};

#endif

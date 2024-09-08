#include "GameBoard.h"
#include "Item.h"
#include "GameState.h"
#include "Engine.h"
#include <ncurses.h>

GameBoard::GameBoard(BoardType b): Board{nullptr}, boardtype{b} {
  refresh();
  mvwprintw(Board, 11, 30, "Press any key to begin.");
  box(Board, 0, 0);
  wrefresh(Board);
  refresh();
}

ErrorCode GameBoard::resize(int rows, int cols) {
  resizeterm(rows, cols);
  // wrefresh(Board);
  refresh();
  return Success;
}

ErrorCode GameBoard::init() {
  Board = newwin(25, 80, 0, 0);
  box(Board, 0, 0);
  wrefresh(Board);
  refresh();
  if (Board) return Success;
  else return InitFailure;
}

ErrorCode GameBoard::drawWin() {
  wclear(Board);
  box(Board, 0, 0);
  mvprintw(12, 35, "YOU WON!");
  mvprintw(13, 28, "Press ENTER to exit...");
  wrefresh(Board);
  refresh();
  nodelay(stdscr, false);
  int ch;
  while ((ch = getch())) {
    if (ch == 10) return Success;
  }
  return Success;
}

ErrorCode GameBoard::drawLose() {
  wclear(Board);
  box(Board, 0, 0);
  mvprintw(12, 35, "YOU LOST!");
  mvprintw(13, 28, "Press ENTER to exit...");
  wrefresh(Board);
  refresh();
  nodelay(stdscr, false);
  int ch;
  while ((ch = getch())) {
    if (ch == 10) return Success;
  }
  return Success;
}

ErrorCode GameBoard::drawState(GameState *gs) {
  wclear(Board);
  const std::vector<Status> *stats = gs->getStats();
  const std::vector<Item *> *items = gs->getItems();
  ErrorCode result = Success;

  for (size_t i = 0, c = stats->size(); i < c; ++i) {
    mvprintw(25+i, 0, "%s: %d", stats->at(i).status.c_str(), stats->at(i).value); 
  }
  for (size_t i = 0, c = items->size(); i < c; ++i) {
    Item *it = items->at(i);
    if (it->draw(Board) != Success) result = DrawFailure;
  }

  box(Board, 0, 0);
  wrefresh(Board);
  refresh();
  return result;
}

WINDOW * GameBoard::getBoard() const { return Board; }

GameBoard::~GameBoard() {
  delwin(Board);
}
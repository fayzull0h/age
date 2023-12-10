#include "GameBoard.h"
#include "Item.h"
#include "Engine.h"
#include <ncurses.h>

GameBoard::GameBoard() {
  refresh();
  Board = newwin(25, 80, 0, 0);
  mvwprintw(Board, 11, 30, "Press any key to begin.");
  wborder(Board, '|', '|', '-', '-', '+', '+', '+', '+');
  wrefresh(Board);
  refresh();
}

ErrorCode GameBoard::addItem(Item *it) {
  if (it) items.emplace_back(it);
  else return ErrorCode::BadRequest;
  return ErrorCode::Success; 
}

ErrorCode GameBoard::drawBoard(Engine *eng) {
  StateType state = eng->getState().type;
  if (state == StateType::NoChange) return ErrorCode::Success;

  if (state == StateType::Items) {
    wclear(Board);
    wborder(Board, '|', '|', '-', '-', '+', '+', '+', '+');
    for (auto i: items) i->draw(Board);
    wrefresh(Board);
  }

  if (eng) {
    std::vector<Status> stats = eng->getStats();
    for (size_t i = 0, c = stats.size(); i < c; ++i) {
      mvprintw(25+i, 0, "%s: %d", stats[i].status.c_str(), stats[i].value); 
    }
  }
  return ErrorCode::Success;
}

ErrorCode GameBoard::notify(Subject<Info, State> &whoFrom) {
  if (drawBoard(static_cast<Engine *>(&whoFrom)) == ErrorCode::Success) {}
  else drawBoard(nullptr);
  notifyObservers();
  wborder(Board, '|', '|', '-', '-', '+', '+', '+', '+');
  wrefresh(Board);
  return ErrorCode::Success;
}

WINDOW * GameBoard::getBoard() const { return Board; }

GameBoard::~GameBoard() {
  delwin(Board);
}
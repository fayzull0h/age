#include "Engine.h"
#include <iostream>
#include "unistd.h"
#include "GameBoard.h"
#include "Item.h"
#include "Rectangle.h"
#include <thread>

Engine::Engine() {
  statcount = 0;
  state = State{StateType::NoChange};
  gb = nullptr;
  initscr();
  nodelay(stdscr, true);
}

State Engine::getState() const {
  return state;
}

ErrorCode Engine::addGameBoard(GameBoard *b) {
  if (b) gb = b;
  else return ErrorCode::BadRequest;
  return ErrorCode::Success;
}

ErrorCode Engine::go() {
  char ch;

  /* Print the initial setup and everything on it */
  state.type = StateType::Items;
  gb->drawBoard(this);
  refresh();
  state.type = StateType::NoChange;

  while (ch = getch()) {
    usleep(50000);
    for (auto &item: items) {
      if (item->doMovement() == ErrorCode::Success) state.type = StateType::Items; 
    }
    gb->drawBoard(this);
    refresh();
    if (ch == 'j') break;
  }

  endwin();
  return ErrorCode::Success;
}

ErrorCode Engine::addStat(const Status &s) {
  switch(statcount++) {
    case 0:
      stat1 = s;
      break;
    case 1:
      stat2 = s;
      break;
    case 2:
      stat3 = s;
      break;
    default:
      return ErrorCode::BadRequest;
  }
  return ErrorCode::Success;
}

ErrorCode Engine::addItem(Item *item) {
  items.emplace_back(item);
  gb->addItem(item);
  return ErrorCode::Success;
}

std::vector<Status> Engine::getStats() const {
  switch(statcount) {
    case 1:
      return std::vector<Status>{stat1};
    case 2:
      return std::vector<Status>{stat1, stat2};
    case 3:
      return std::vector<Status>{stat1, stat2, stat3};
  }
  std::vector<Status> result;
  return result;
}

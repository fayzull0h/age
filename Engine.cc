#include "Engine.h"
#include <iostream>
#include "unistd.h"
#include "GameBoard.h"
#include "Item.h"
#include "GameState.h"

Engine::Engine(GameState *gs, bool (*wincheck)(GameState *)): gb{nullptr},
  gamestate{gs}, wincheck{wincheck} {
  state = EngineState{StateType::NoChange};
  gb = nullptr;
  initscr();
  keypad(stdscr, true);
  noecho();
  nodelay(stdscr, true);
}

EngineState Engine::getEngineState() const { return state; }

ErrorCode Engine::addGameBoard(GameBoard *b) {
  if (b) {
    gb = b;
    gb->init();
  } else return BadRequest;
  return Success;
}

ErrorCode Engine::addInputHandler(bool (*ih)(const int&, GameState *)) {
  if (ih) inputHandler = ih;
  else return BadRequest;
  return Success;
}

ErrorCode Engine::go() {
  bool game = true;
  int ch;

  while (game) {
    /* Get input and pass it to the input handler (provided by game programmer) */
    ch = getch();
    game = inputHandler(ch, gamestate);
    flushinp();

    /* Send tick to all pieces */
    for (int i = 0, c = gamestate->items.size(); i < c; ++i) {
      gamestate->items[i]->tick(gb);
    }

    /* Draw the board and refresh the screen */
    gb->drawState(gamestate);
    refresh();
    usleep(50000);
  }

  endwin();
  return Success;
}

Engine::~Engine() { 
  // for (auto &it: items) it = nullptr;
  if (gb) gb = nullptr;
  // if (player) player = nullptr;
}


#include "Engine.h"
#include <iostream>
#include "unistd.h"
#include "GameBoard.h"
#include "Item.h"
#include "GameState.h"

Engine::Engine(GameState *gs, bool (*wincheck)(GameState *), bool (*losecheck)(GameState *)): gb{nullptr},
  gamestate{gs}, wincheck{wincheck}, losecheck{losecheck} {
  gb = nullptr;
  initscr();
  keypad(stdscr, true);
  noecho();
  nodelay(stdscr, true);
}

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

    /* Send tick to game state */
    ErrorCode result = gamestate->tick(gb->boardtype);

    /* Check if the game has been won yet */
    if (result == GameWon || wincheck(gamestate)) {
      gb->drawWin();
      break;
    }

    if (losecheck(gamestate)) {
      gb->drawLose();
      break;
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


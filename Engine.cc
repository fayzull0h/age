#include "Engine.h"
#include <iostream>
#include "unistd.h"
#include "GameBoard.h"
#include "Item.h"
#include "GameState.h"

Engine::Engine(GameState *gs, ErrorCode (*wincheck)(GameState *), ErrorCode (*losecheck)(GameState *)):
 gb{nullptr}, gamestate{gs}, wincheck{wincheck}, losecheck{losecheck} {
  gb = nullptr;
  initscr();
  keypad(stdscr, true);
  noecho();
  nodelay(stdscr, true);
  start_color();
  init_pair(255, COLOR_WHITE, COLOR_BLACK);
  attron(COLOR_PAIR(255));
}

ErrorCode Engine::addGameBoard(GameBoard *b) {
  if (b) {
    gb = b;
    gb->init();
  } else return BadRequest;
  return Success;
}

ErrorCode Engine::addInputHandler(ErrorCode (*ih)(const int&, GameState *)) {
  if (ih) inputHandler = ih;
  else return BadRequest;
  return Success;
}

ErrorCode Engine::go() {
  ErrorCode game = GameContinue;
  int ch;

  while (game == GameContinue) {
    /* Get input and pass it to the input handler (provided by game programmer) */
    ch = getch();
    game = inputHandler(ch, gamestate);
    flushinp();

    /* Send tick to game state */
    ErrorCode result = gamestate->tick(gb->boardtype);

    /* Check if the game has been won yet */
    if (result == GameWon || wincheck(gamestate) == GameWon) {
      gb->drawWin();
      break;
    }

    if (losecheck(gamestate) == GameLost || result == GameLost) {
      gb->drawLose();
      break;
    }

    /* Draw the board and refresh the screen */
    gb->drawState(gamestate);
    refresh();
    usleep(30000);
  }

  endwin();
  return Success;
}

Engine::~Engine() { 
  attroff(COLOR_PAIR(1));
  if (gb) gb = nullptr;
  if (gamestate) gamestate = nullptr;
}


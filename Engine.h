#ifndef ENGINE_H
#define ENGINE_H

#include "metadata.h"
#include <vector>
#include "Item.h"

class GameBoard;
class GameState;

class Engine {
  // std::vector<Status> stats;
  // std::vector<Item *> items;
  GameBoard *gb; 
  // Item *player;

  GameState *gamestate;
  bool (*inputHandler)(const int&, GameState *);
  bool (*wincheck)(GameState *);

 public:
  Engine(GameState *gs, bool (*wincheck)(GameState *));
  ErrorCode go();
  ErrorCode addGameBoard(GameBoard *gb);
  ErrorCode addInputHandler(bool (*ih)(const int&, GameState *));
  ~Engine();
};



#endif

/** old game loop keyboard input handler 
if (player) { 
  switch(ch) {
    case 'w':
      player->addY(-1);
      break;
    case 's':
      player->addY(1);
      break;
    case 'd':
      player->addX(1);
      break;
    case 'a':
      player->addX(-1);
      break;
    case KEY_UP:
      player->addY(-1);
      break;
    case KEY_DOWN:
      player->addY(1);
      break;
    case KEY_RIGHT:
      player->addX(1);
      break;
    case KEY_LEFT:
      player->addX(-1);
      break;
    default:
      break;
  }
}
*/

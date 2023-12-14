#include "Engine.h"
#include "Single.h"
#include "GameBoard.h"
#include "metadata.h"
#include "Rectangle.h"
#include "Item.h"
#include "Bitmap.h"
#include "Movements.h"
#include "GameState.h"

#include <ncurses.h>

#include <iostream>

bool testwin(GameState *gs) { return false; }
bool inputHandler(const int &ch, GameState *gs) {
  if (ch == KEY_F(1)) return false;
  Item *player = gs->getPlayer();
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
  return true;
}

int main() { 
  GameBoard gb{Solid};
  GameState game{};

  Status s1{"RectPos", 1};

  Rectangle fr{1, 1, 10, 5, 10, '#'}; 
  Rectangle dollar{1, 1, 4, 4, 4, '$'};

  LinearMovement<Right> frMoveRight{15};
  LinearMovement<Down> moveDown{-1};

  PeriodicMovement blink = PeriodicMovement();

  Single blank{-1, -1, -1, ' '};
  blink.addForm(&blank);

  dollar.addMovement(&moveDown);

  std::vector<Triple> playerbitmap = {
    Triple{40, 20, '@'},
    Triple{40, 21, '#'},
    Triple{40, 22, '#'},
    Triple{39, 21, '#'},
    Triple{38, 22, '/'},
    Triple{39, 23, '#'},
    Triple{39, 24, '|'},
    Triple{41, 21, '#'},
    Triple{41, 23, '#'},
    Triple{41, 24, '|'},
    Triple{42, 22, '\\'}
  };

  Bitmap player{playerbitmap, 0};

  Engine e = Engine(&game, &testwin);

  e.addGameBoard(&gb);
  e.addInputHandler(&inputHandler);

  game.addItem(&fr);
  game.addItem(&dollar);
  game.addPlayer(&player);
  game.addStat(s1);
  e.go();
}

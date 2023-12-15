#include "Engine.h"
#include "Item.h"
#include "Single.h"
#include "Rectangle.h"
#include "Bitmap.h"
#include "GameBoard.h"
#include "metadata.h"
#include "Movements.h"
#include "GameState.h"
#include "Collision.h"

class BrickGame: public GameState {
  int tickCounter = 0;
 public:
  ErrorCode tick(BoardType btype) override {
    if (!(tickCounter++ % 3 == 0)) return Success;
    ErrorCode result = Success;
    for (size_t i = 0, c = items.size(); i < c; ++i) {
      result = items[i]->tick(this, btype);
    }
    if (result == DeleteOther) {
      stats[0].value += 100;
    }
    return Success;
  }
};

bool handleInputs(const int &ch, GameState *gs) {
  if (ch == KEY_F(1)) return false;
  Item *player = gs->getPlayer();
  switch(ch) {
    case KEY_LEFT:
      if (player->getX() > 1) player->addX(-3);
      return true;
    case KEY_RIGHT:
      if (player->getX()+player->getWidth() < 79) player->addX(3);
      return true;
    default:
      return true;
  }
}

class Block: public Item {
  Bitmap bitmap;
 public:
  Block(int x, int y, int z): Item{x, y, z} {
    std::vector<Triple> *blockMap = new std::vector<Triple>{
      Triple{x, y, '+'},
      Triple{x+1, y, '-'},
      Triple{x+2, y, '-'},
      Triple{x+3, y, '-'},
      Triple{x+4, y, '-'},
      Triple{x+5, y, '+'},
      Triple{x+5, y+1, '|'},
      Triple{x+5, y+2, '|'},
      Triple{x+5, y+3, '+'},
      Triple{x+1, y+3, '-'},
      Triple{x+2, y+3, '-'},
      Triple{x+3, y+3, '-'},
      Triple{x+4, y+3, '-'},
      Triple{x, y+3, '+'},
      Triple{x, y+2, '|'},
      Triple{x, y+1, '|'}
    };
    bitmap = Bitmap{*blockMap, z};
  }
  int getHeight() override { return 4; }
  int getWidth() override { return 6; }
  ErrorCode draw(WINDOW *Board) override {
    return bitmap.draw(Board);
  }
};

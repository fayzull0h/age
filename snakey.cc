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

#include <random>
#include <iostream>

class EatCollision: public Collision {
 public:
  EatCollision(Item *snake, Item *apple): Collision{snake, apple} {}
  ErrorCode collide(CollisionCode code) {
    /*int vx = it1->getXV(), vy = it1->getYV();
    if (vx == 0) {
      if (vy > 0 && vy < 3) it1->setYV(++vy);
      if (vy < 0 && vy > -3) it1->setYV(--vy);
    } else if (vy == 0) {
      if (vx > 0 && vx < 3) it1->setXV(++vx);
      if (vx < 0 && vx > -3) it1->setXV(--vx);
    }*/
    it2->setX((rand() % 79) + 1);
    it2->setY((rand() % 24) + 1);
    return Collided;
  }
};

class SnakeGame: public GameState {
 public:
  ErrorCode tick(BoardType btype) override {
    ErrorCode result = Success;
    for (size_t i = 0, c = items.size(); i < c; ++i) {
      Item *item = items[i];
      result = item->tick(this, btype); 
      if (result == Deleted) {
        items.erase(items.begin()+i);
      }
    }
    if (result == Collided) stats[0].value += 1;
    return result;
  }
};

bool handleInputs(const int &ch, GameState *gs) {
  if (ch == KEY_F(1)) return false;
  Item *player = gs->getPlayer();
  int vx = player->getXV(), vy = player->getYV();
  switch(ch) {
    case KEY_UP:
      if (vy == 0) {
        player->setYV(-abs(vx/2));
        player->setXV(0);
      }
      return true;
    case KEY_DOWN:
      if (vy == 0) {
        player->setYV(abs(vx/2));
        player->setXV(0);
      }
      return true;
    case KEY_RIGHT:
      if (vx == 0) {
        player->setXV(abs(vy));
        player->setYV(0);
      }
      return true;
    case KEY_LEFT:
      if (vx == 0) {
        player->setXV(-abs(vy));
        player->setYV(0);
      }
      return true;
    default:
      break;
  }
  return true;
}

bool wincheck(GameState *gs) {
  if (gs->getStats()->at(0).value == 10) return true;
  return false;
}

class WinMessage: public Item {
 public:
  int getHeight() override { return 1; }
  int getWidth() override { return 15; }
  ErrorCode draw(WINDOW *Board) override {
    if (periodicMovement) {
      if (periodicMovement->getPos() != 0) return periodicMovement->draw(Board);
    }
    mvprintw(12, 35, "YOU WON!");
    return Success;
  }
};

bool losecheck(GameState *gs) { return false; }

int main() {
  SnakeGame game{};
  GameBoard gb{Solid};

  Status score{"Score", 0};

  Single blank{-1, -1, -1, ' '};
  PeriodicMovement blink{};
  blink.addForm(&blank);

  Rectangle snakehead(39, 12, 0, 2, 2, 'O');
  snakehead.setYV(2);
  Single apple(50, 12, 1, 'X');std::vector<Triple> playerbitmap = {
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

  Bitmap b {playerbitmap, 0};
  //snakehead.setPeriodicMovement(&blink);
  // snakehead.setXV(-1);


  Engine e{&game, &wincheck, &losecheck};


  e.addGameBoard(&gb);
  e.addInputHandler(&handleInputs);

  EatCollision snakeEatApple(&snakehead, &apple);
  game.addCollision(&snakeEatApple);

  game.addItem(&apple);
  game.addItem(&b);
  game.addPlayer(&snakehead);
  game.addStat(score);
  std::cin.get();
  e.go();
}

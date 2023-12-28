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

// #define DEBUG

class EatCollision: public Collision {
 public:
  EatCollision(Item *snake, Item *apple): Collision{snake, apple} {}
  ErrorCode collide(CollisionCode code) override {
    it2->setX((rand() % 78) + 1);
    it2->setY((rand() % 23) + 1);
    return Collided; 
  }
};

class LoseCollision: public Collision {
 public:
  LoseCollision(Item *snakehead, Item *tailpiece): Collision{snakehead, tailpiece} {}
  ErrorCode collide(CollisionCode code) override { return GameLost; }
};

class SnakeGame: public GameState {
  size_t ticks = 0;
  std::vector<Item *> tail;
 public:
  SnakeGame(): GameState{} {}

  ErrorCode initTail() {
    Single * s1 = new Single{38, 12, 1, '#', COLOR_GREEN};
    Single * s2 = new Single{37, 12, 1, '#', COLOR_GREEN};
    Single * s3 = new Single{36, 12, 1, '#', COLOR_GREEN};
    addCollision(new LoseCollision{player, s1});
    addCollision(new LoseCollision{player, s2});
    addCollision(new LoseCollision{player, s3});
    tail.emplace_back(s1);
    tail.emplace_back(s2);
    tail.emplace_back(s3);
    items.emplace_back(s1);
    items.emplace_back(s2);
    items.emplace_back(s3);
    return Success;
  }

  ErrorCode resetTicks() { ticks = 1; return GameContinue; }
  
  bool appleInTail() const {
    for (auto tailpiece: tail) {
      #ifdef DEBUG
        mvprintw(29, 1, "tailX: %d, appleX: %d", tailpiece->getX(), items[1]->getX());
        mvprintw(28, 1, "tailY: %d, appleY: %d", tailpiece->getY(), items[1]->getY());
        refresh();
      #endif
      if (items[1]->getX() == tailpiece->getX() && items[1]->getY() == tailpiece->getY()) {
        return true;
      }
    }
    #ifdef DEBUG
      mvaddch(30, 1, 'O');
    #endif
    return false;
  }

  ErrorCode tick(BoardType btype) override {
    if (player->getXV()) {}
    else if (++ticks == 2) ticks = 0; 
    else return GameContinue;

    for (size_t i = 0, c = tail.size()-1; i < c; ++i) {
      tail[i]->setX(tail[i+1]->getX());
      tail[i]->setY(tail[i+1]->getY());
    }
    tail[tail.size()-1]->setX(player->getX());
    tail[tail.size()-1]->setY(player->getY());

    ErrorCode result = player->tick(this, Solid);
    if (result == Collided) {
      while (appleInTail()) {
        items[1]->setX((rand() % 78) + 1);
        items[1]->setY((rand() % 23) + 1);
      }
      stats[0].value += 1;
      Single * s = new Single{player->getX(), player->getY(), 1, '#', COLOR_GREEN};
      addCollision(new LoseCollision{player, s});
      tail.emplace_back(s);
      items.emplace_back(s);
      return GameContinue;
    } else if (result == VerticalWallCollision || result == HorizontalWallCollision) return GameLost;
    else if (result == GameLost) return GameLost;
    return GameContinue;
  }

  ~SnakeGame() {
    for (size_t i = 2, c = items.size(); i < c; ++i) {
      Item *tmp = items[i];
      items[i] = nullptr;
      delete tmp;
    }
    for (size_t i = 0, c = collisions.size(); i < c; ++i) {
      delete collisions[i];
    }
  }
};

ErrorCode handleInputs(const int &ch, GameState *gs) {
  if (ch == KEY_F(1)) return GameExit;
  Item *player = gs->getPlayer();
  int vx = player->getXV(), vy = player->getYV();

  SnakeGame * sg = static_cast<SnakeGame *>(gs);

  switch(ch) {
    case KEY_UP:
      if (vy == 0) {
        player->setYV(-1);
        player->setXV(0);
      }
      sg->resetTicks();
      return GameContinue;
    case KEY_DOWN:
      if (vy == 0) {
        player->setYV(1);
        player->setXV(0);
      }
      sg->resetTicks();
      return GameContinue;
    case KEY_RIGHT:
      if (vx == 0) {
        player->setXV(1);
        player->setYV(0);
      }
      return GameContinue;
    case KEY_LEFT:
      if (vx == 0) {
        player->setXV(-1);
        player->setYV(0);
      }
      return GameContinue;
    default:
      break;
  }
  return GameContinue;
}

ErrorCode wincheck(GameState *gs) {
  if (gs->getStats()->at(0).value == 150) return GameWon;
  return GameContinue;
}

ErrorCode losecheck(GameState *gs) { return GameContinue; }

int main() {
  SnakeGame game{};
  GameBoard gb{Solid};

  Status score{"Score", 0};

  Single snakehead(39, 12, 1, 'O', COLOR_GREEN);
  snakehead.setXV(1);
  Single apple (50, 12, 1, 'X', COLOR_RED);

  Engine e{&game, &wincheck, &losecheck};

  e.addGameBoard(&gb);
  e.addInputHandler(&handleInputs);

  game.addCollision(new EatCollision{&snakehead, &apple});

  game.addItem(&apple);
  game.addPlayer(&snakehead);
  game.initTail();
  game.addStat(score);
  e.go();
}

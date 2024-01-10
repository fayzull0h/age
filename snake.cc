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
// #define LVL2
// #define LVL5

class EatCollision: public CollisionTemplate {
 public:
  EatCollision(Item *snake, Item *apple): CollisionTemplate{snake, apple} {}
  ErrorCode collide(CollisionCode code) override {
    it2->setX((rand() % 78) + 1);
    it2->setY((rand() % 23) + 1);
    return Collided; 
  }
};

class LoseCollision: public CollisionTemplate {
 public:
  LoseCollision(Item *snakehead, Item *tailpiece): CollisionTemplate{snakehead, tailpiece} {}
  ErrorCode collide(CollisionCode code) override { return GameLost; }
};

class SnakeGame: public GameState {
  size_t ticks = 0;
  std::vector<Item *> tail;
  Item *apple;
 public:
  SnakeGame(): GameState{}, apple{nullptr} {}

  ErrorCode initTail() {
    Single * s1 = new Single{38, 12, 1, '#', COLOR_GREEN, COLOR_BLACK};
    Single * s2 = new Single{37, 12, 1, '#', COLOR_GREEN, COLOR_BLACK};
    Single * s3 = new Single{36, 12, 1, '#', COLOR_GREEN, COLOR_BLACK};
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

  ErrorCode addApple(Item *a) {
    if (a == nullptr) return BadRequest;
    apple = a;
    return addItem(a);
  }

  ErrorCode resetTicks() { ticks = 1; return GameContinue; }
  
  bool appleInTail() const {
    for (auto tailpiece: items) {
    // for (size_t i = 2, c = items.size(); i < c; ++i) {
      if (tailpiece == apple) continue;
      #ifdef DEBUG
        mvprintw(29, 1, "tailX: %d, appleX: %d", tailpiece->getX(), items[1]->getX());
        mvprintw(28, 1, "tailY: %d, appleY: %d", tailpiece->getY(), items[1]->getY());
        refresh();
      #endif
      if (apple->getX() == tailpiece->getX() && apple->getY() == tailpiece->getY()) {
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
        apple->setX((rand() % 78) + 1);
        apple->setY((rand() % 23) + 1);
      }
      stats[0].value += 1;
      Single * s = new Single{player->getX(), player->getY(), 1, '#', COLOR_GREEN, COLOR_BLACK};
      addCollision(new LoseCollision{player, s});
      tail.emplace_back(s);
      items.emplace_back(s);
      return GameContinue;
    } else if (result >= LowerWallCollision && result < 400) return GameLost;
    else if (result == GameLost) return GameLost;
    return GameContinue;
  }

  ~SnakeGame() {
    for (size_t i = 0, c = items.size(); i < c; ++i) {
      if (items[i] == player || items[i] == apple) continue;
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

int main(int argc, char * argv[]) {
  int lvl = 1;
  if (argc > 1) {
    if (argv[1][1] == 'l') {
      lvl = atoi(argv[2]);
    }
  }
  SnakeGame game{};
  GameBoard gb{Solid};

  Status score{"Score", 0};

  Single snakehead(39, 12, 1, 'O', COLOR_GREEN,COLOR_BLACK);
  snakehead.setXV(1);
  Single apple(50, 12, 1, 'X', COLOR_RED, COLOR_BLACK);

  Engine e{&game, &wincheck, &losecheck};

  e.addGameBoard(&gb);
  e.addInputHandler(&handleInputs);

  game.addCollision(new EatCollision{&snakehead, &apple});

  game.addApple(&apple);
  game.addPlayer(&snakehead);
  mvprintw(25, 36, "Level %d", lvl);

  if (lvl == 2) {
    for (size_t i = 0; i < 10; ++i) {
      Single *s1 = new Single(20, 25-(i+1), 1, ' ', COLOR_BLUE, COLOR_BLUE);
      Single *s2 = new Single(40, (i+1), 1, ' ', COLOR_BLUE, COLOR_BLUE);
      Single *s3 = new Single(60, 25-(i+1), 1, ' ', COLOR_BLUE, COLOR_BLUE);
      game.addCollision(new LoseCollision(&snakehead, s1));
      game.addCollision(new LoseCollision(&snakehead, s2));
      game.addCollision(new LoseCollision(&snakehead, s3));
      game.addItem(s1);
      game.addItem(s2);
      game.addItem(s3);
    }
  } else if (lvl == 5) {
    /* left and right walls */
    for (size_t i = 0; i < 20; ++i) {
      Single *s1 = new Single(i+1, 8, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      Single *s2 = new Single(i+1, 17, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      Single *s3 = new Single(80-(i+1), 8, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      Single *s4 = new Single(80-(i+1), 17, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      game.addCollision(new LoseCollision(&snakehead, s1));
      game.addCollision(new LoseCollision(&snakehead, s2));
      game.addCollision(new LoseCollision(&snakehead, s3));
      game.addCollision(new LoseCollision(&snakehead, s4));
      game.addItem(s1);
      game.addItem(s2);
      game.addItem(s3);
      game.addItem(s4);
    }
    for (size_t i = 0; i < 2; ++i) {
      Single *s1 = new Single(20, 9+i, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      Single *s2 = new Single(20, 15+i, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      Single *s3 = new Single(60, 9+i, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      Single *s4 = new Single(60, 15+i, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      game.addCollision(new LoseCollision(&snakehead, s1));
      game.addCollision(new LoseCollision(&snakehead, s2));
      game.addCollision(new LoseCollision(&snakehead, s3));
      game.addCollision(new LoseCollision(&snakehead, s4));
      game.addItem(s1);
      game.addItem(s2);
      game.addItem(s3);
      game.addItem(s4);
    }

    for (size_t i = 0; i < 4; ++i) {
      /* top left */
      Single *s1 = new Single(20, i+1, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      Single *s2 = new Single(i+1, 4, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      Single *s3 = new Single(i+4, 4, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      game.addCollision(new LoseCollision(&snakehead, s1));
      game.addCollision(new LoseCollision(&snakehead, s2));
      game.addCollision(new LoseCollision(&snakehead, s3));
      game.addItem(s1);
      game.addItem(s2);
      game.addItem(s3);

      /* top right */
      Single *s4 = new Single(60, i+1, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      Single *s5 = new Single(80-(i+1), 4, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      Single *s6 = new Single(80-(i+4), 4, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      game.addCollision(new LoseCollision(&snakehead, s4));
      game.addCollision(new LoseCollision(&snakehead, s5));
      game.addCollision(new LoseCollision(&snakehead, s6));
      game.addItem(s4);
      game.addItem(s5);
      game.addItem(s6);

      /* bottom left */
      Single *s7 = new Single(20, 25-(i+1), 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      Single *s8 = new Single(i+1, 21, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      Single *s9 = new Single(i+4, 21, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      game.addCollision(new LoseCollision(&snakehead, s7));
      game.addCollision(new LoseCollision(&snakehead, s8));
      game.addCollision(new LoseCollision(&snakehead, s9));
      game.addItem(s7);
      game.addItem(s8);
      game.addItem(s9);

      /* bottom right */
      Single *s10 = new Single(60, 25-(i+1), 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      Single *s11 = new Single(80-(i+1), 21, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      Single *s12 = new Single(80-(i+4), 21, 1, ' ', COLOR_YELLOW, COLOR_YELLOW);
      game.addCollision(new LoseCollision(&snakehead, s10));
      game.addCollision(new LoseCollision(&snakehead, s11));
      game.addCollision(new LoseCollision(&snakehead, s12));
      game.addItem(s10);
      game.addItem(s11);
      game.addItem(s12);
    }
  } else if (lvl != 1) {
    mvprintw(26, 0, "Level %d has not been made yet, stay tuned...", lvl);
  }

  game.initTail();
  game.addStat(score);
  e.go();
}

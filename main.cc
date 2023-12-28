#include "BrickBreaker.h"

bool wincheck(GameState *gs) { 
  const std::vector<Item *> *items = gs->getItems();
  return (items->size() == 1);
}

bool losecheck(GameState *gs) {
  const std::vector<Item *> *items = gs->getItems();
  Item *ball = items->at(0);
  return (ball->getY()+ball->getHeight()) >= 23;
}

int main() {
  BrickGame game{};
  GameBoard gb{Solid};

  Status score{"Score", 0};

  Rectangle ball{37, 20, 1, 2, 3, '+'};
  ball.setYV(-1);
  ball.setXV(-1);
  game.addItem(&ball);

  for (int i = 0; i < 13; ++i) {
    char c = '$', a = 'O';
    if (i % 2 == 0) c = 'O', a = '$';
    Rectangle *b1 = new Rectangle{6 * i+1, 1, 0, 4, 6, c};
    // Rectangle *b2 = new Rectangle{6 * i+1, 5, 0, 4, 6, a};

    StopCollision *d1 = new StopCollision{&ball, b1};
    // BounceCollision *d2 = new BounceCollision{&ball, b2};

    game.addCollision(d1);
    // game.addCollision(d2);

    game.addItem(b1);
    // game.addItem(b2);
    // delete d1;
  }

  Rectangle bar{30, 22, 1, 2, 15, '#'};
  game.addPlayer(&bar);
  BounceCollision barBall{&ball, &bar};
  game.addCollision(&barBall);

  Engine e{&game, &wincheck, &losecheck};

  e.addGameBoard(&gb);
  e.addInputHandler(&handleInputs);

  game.addStat(score);

  e.go();
}

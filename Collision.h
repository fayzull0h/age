#ifndef COLLISION_H
#define COLLISION_H

#include "metadata.h"

class Item;

class Collision {
 protected:
  Item *it1;
  Item *it2;
 public:
  Collision(Item *i, Item *k): it1{i}, it2{k} {}
  ErrorCode checkCollision();
  Item *getItem1() { return it1; }
  Item *getItem2() { return it2; }
  virtual ErrorCode collide(CollisionCode code) = 0;
  ~Collision() {
    if (it1) it1 = nullptr;
    if (it2) it2 = nullptr;
  }
};

class BounceCollision: public Collision {
 public:
  BounceCollision(Item *k, Item *j): Collision{k, j} {}
  ErrorCode collide(CollisionCode code) override;
};

class StopCollision: public Collision {
 public:
  StopCollision(Item *k, Item *j): Collision{k, j} {}
  ErrorCode collide(CollisionCode code) override;
};

class DestroyCollision: public Collision {
 public:
  DestroyCollision(Item *k, Item *j): Collision{k, j} {}
  ErrorCode collide(CollisionCode code) override;
};

class WinCollision: public Collision {
 public:
  WinCollision(Item *k, Item *j): Collision{k, j} {}
  ErrorCode collide(CollisionCode code) override;
};

/* the following would be provided by the game programmer */

#endif

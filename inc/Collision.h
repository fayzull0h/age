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
  virtual ErrorCode checkCollision() = 0;
  Item *getItem1() { return it1; }
  Item *getItem2() { return it2; }
  virtual ErrorCode collide(CollisionCode code) = 0;
  virtual ~Collision();
};

class CollisionTemplate: public Collision {
 public:
  CollisionTemplate(Item *it1, Item *it2): Collision{it1, it2} {}
  ErrorCode checkCollision() override;
};

class BounceCollision: public CollisionTemplate {
 public:
  BounceCollision(Item *k, Item *j): CollisionTemplate{k, j} {}
  ErrorCode collide(CollisionCode code) override;
};

class StopCollision: public CollisionTemplate {
 public:
  StopCollision(Item *k, Item *j): CollisionTemplate{k, j} {}
  ErrorCode collide(CollisionCode code) override;
};

class DestroyCollision: public CollisionTemplate {
 public:
  DestroyCollision(Item *k, Item *j): CollisionTemplate{k, j} {}
  ErrorCode collide(CollisionCode code) override;
};

class WinCollision: public CollisionTemplate {
 public:
  WinCollision(Item *k, Item *j): CollisionTemplate{k, j} {}
  ErrorCode collide(CollisionCode code) override;
};

/* the following would be provided by the game programmer */

#endif

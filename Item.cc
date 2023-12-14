#include "Item.h"
#include "Movements.h"
#include "GameState.h"
#include "Collision.h"

Item::Item(int x, int y, int z): x{x}, y{y}, z{z}, ticksOffScreen{0},
  xvelocity{0}, yvelocity{0}, periodicMovement{nullptr} {}

int Item::getX() { return x; }

int Item::getY() { return y; }

int Item::getZ() { return z; }

ErrorCode Item::setPeriodicMovement(PeriodicMovement *pm) {
  if (pm) periodicMovement = pm;
  else throw BadRequest;
  return Success;
}

ErrorCode Item::setMovement(Movement *m) {
  try {
    if (m->getType() == Up) { yvelocity = m->magnitude(); }
    else if (m->getType() == Down) { yvelocity = m->magnitude(); }
    else if (m->getType() == Right) { xvelocity = m->magnitude(); }
    else if (m->getType() == Left) { xvelocity = m->magnitude(); }
  } catch(...) { throw; }
  return Success; 
}

ErrorCode Item::addX(int i) {
  x += i;
  return Success; 
}

ErrorCode Item::addY(int i) {
  y += i;
  return Success; 
}

ErrorCode Item::addZ(int i) {
  z += i;
  return Success; 
}

ErrorCode Item::tick(GameState *gs, GameBoard *gb) {
  if (getTicks() > 10) return Deleted;
  if (periodicMovement) periodicMovement->move();

  if (gb->boardtype == Solid) {
    if (x+xvelocity < 0 || x+xvelocity+getWidth()>79) reverseXV();
    if (y+yvelocity < 0 || y+yvelocity+getHeight()>24) reverseYV();
  }

  addX(xvelocity);
  addY(yvelocity);

  std::vector<Collision *> *collisions = gs->getCollisions();
  ErrorCode result = Success;

  for (size_t i = 0, c = collisions->size(); i < c; ++i) {
    result = collisions->at(i)->checkCollision();
  }

  return result;
}

int Item::getTicks() const { return ticksOffScreen; }

ErrorCode Item::addTick() { 
  if (++ticksOffScreen > 10) return Deleted;
  else return NoMovement;
}

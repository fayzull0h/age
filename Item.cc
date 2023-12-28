#include "Item.h"
#include "Movements.h"
#include "GameState.h"
#include "Collision.h"

int Item::id_counter = 1;

Item::Item(int x, int y, int z, int color): x{x}, y{y}, z{z}, ticksOffScreen{0},
  xvelocity{0}, yvelocity{0}, id{id_counter++}, color{color}, periodicMovement{nullptr} {}

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

ErrorCode Item::tick(GameState *gs, BoardType btype) {
  if (ticksOffScreen > 10) return Deleted;
  if (periodicMovement) periodicMovement->move();

  if (btype == Solid) {
    if (x+xvelocity < 1 || x+xvelocity+getWidth()>79) return HorizontalWallCollision;
    if (y+yvelocity < 1 || y+yvelocity+getHeight()>24) return VerticalWallCollision;
  } else if (x > 1 && x < 79 && y > 1 && y < 24) ticksOffScreen = 0;
  else addTick();

  addX(xvelocity);
  addY(yvelocity);

  std::vector<Collision *> *collisions = gs->getCollisions();
  ErrorCode result = NoMovement;

  for (size_t i = 0, c = collisions->size(); i < c; ++i) {
    ErrorCode newResult = collisions->at(i)->checkCollision();
    if (newResult == DeleteOther) {
      gs->deleteItem(collisions->at(i)->getItem2());
    } else if (result == DeleteMe) {
      gs->deleteItem(this);
    } else if (result == DeleteBoth) {
      gs->deleteItem(collisions->at(i)->getItem2());
      gs->deleteItem(this);
    }
    if (newResult != NoMovement) result = newResult;
  }

  return result;
}

ErrorCode Item::addTick() { 
  if (++ticksOffScreen > 10) return Deleted;
  else return NoMovement;
}

int Item::setXV(int n) { return xvelocity = n;}
int Item::setYV(int n) { return yvelocity = n;}

int Item::setColor(int c) { return color = c; }

#include "Item.h"
#include "Movements.h"
#include "GameState.h"
#include "Collision.h"

int Item::id_counter = 1;

Item::Item(int x, int y, int z, int front, int back): x{x}, y{y}, z{z}, ticksOffScreen{0}, xvelocity{0}, 
  yvelocity{0}, id{id_counter++}, frontColor{front}, backColor{back}, periodicMovement{nullptr} {}

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
  ErrorCode result = NoMovement;

  if (btype == Solid) {
    if (xvelocity < 0 && x+xvelocity < 1) result = LeftWallCollision;
    else if (xvelocity > 0 && x+xvelocity+getWidth()>79) result = RightWallCollision;
    if (yvelocity < 0 && y+yvelocity < 1) result = UpperWallCollision;
    else if (yvelocity > 0 && y+yvelocity+getHeight()>24) result = LowerWallCollision;
  }
  else addTick();

  addX(xvelocity);
  addY(yvelocity);

  if (result != NoMovement) return result;

  std::vector<Collision *> *collisions = gs->getCollisions();

  for (size_t i = 0, c = collisions->size(); i < c; ++i) {
    ErrorCode newResult;
    if (collisions->at(i)->getItem1() == this || collisions->at(i)->getItem2() == this) {
      newResult = collisions->at(i)->checkCollision();
    }
    else continue;

    if (newResult == DeleteOther) {
      gs->nullifyItem(collisions->at(i)->getItem2());
    } else if (result == DeleteMe) {
      gs->deleteItem(this);
    } else if (result == DeleteBoth) {
      gs->deleteItem(collisions->at(i)->getItem2());
      gs->deleteItem(this);
    }
    if (newResult != NoMovement) result = newResult;
  }
  gs->deleteNulls();

  return result;
}

ErrorCode Item::addTick() { 
  if (++ticksOffScreen > 10) return Deleted;
  else return NoMovement;
}

int Item::setXV(int n) { return xvelocity = n;}
int Item::setYV(int n) { return yvelocity = n;}

int Item::setColors(int f, int b) {
  frontColor = f;
  backColor = b;
  return 0;
}

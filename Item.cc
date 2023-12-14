#include "Item.h"
#include "Movements.h"

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

/* TO DELETE 
ErrorCode Item::doMovements(GameBoard *gb) {
  for (size_t i = 0, c = movements.size(); i < c; ++i) {
    Movement *m = movements[i];
    if (m->getType() == MovementType::Linear) {
      ErrorCode result = m->move(gb, this);
      if (result == DeleteMe) return DeleteMe;
      else if (result == DeleteMove) {
        movements.erase(movements.begin()+i);
        return Success;
      }
    }
  }
  return Success;
}
*/

ErrorCode Item::tick(GameBoard *gb) {
  if (getTicks() > 10) return DeleteMe;
  if (periodicMovement) periodicMovement->move(gb, this);
  addX(xvelocity);
  addY(yvelocity);
  // return doMovements(gb);
  return Success;
}

int Item::getTicks() const { return ticksOffScreen; }

ErrorCode Item::addTick() { 
  if (++ticksOffScreen > 10) return DeleteMe;
  else return NoMovement;
}

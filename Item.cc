#include "Item.h"
#include "PeriodicMovement.h"

Item::Item(int x, int y, int z): x{x}, y{y}, z{z}, movement{PeriodicMovement{0, 0, 0, 0}} {}

Item::Item(int x, int y, int z, PeriodicMovement &pm): x{x}, y{y}, z{z}, movement{pm} {}

ErrorCode Item::notify(Subject<Info, State> &whoFrom) { 
  //draw(whoFrom.getBoard()); 
  return ErrorCode::Success;
}

ErrorCode Item::setMovement(PeriodicMovement &pm) { 
  movement = pm;
  return ErrorCode::Success;
}

PeriodicMovement &Item::getMovement() { return movement; }

int Item::getX() const { return x; }

int Item::getY() const { return y; }

int Item::getZ() const { return z; }

ErrorCode Item::addX(int i) {
  x += i;
  return ErrorCode::Success; 
}

ErrorCode Item::addY(int i) {
  y += i;
  return ErrorCode::Success; 
}

ErrorCode Item::addZ(int i) {
  z += i;
  return ErrorCode::Success; 
}

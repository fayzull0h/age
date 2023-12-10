#include "Item.h"
#include "PeriodicMovement.h"

Item::Item(int x, int y, int z): x{x}, y{y}, z{z}, movement{nullptr} {}

Item::Item(int x, int y, int z, PeriodicMovement *pm): x{x}, y{y}, z{z}, movement{pm} {}

ErrorCode Item::notify(Subject<Info, State> &whoFrom) { 
  //draw(whoFrom.getBoard()); 
  return ErrorCode::Success;
}

ErrorCode Item::setMovement(PeriodicMovement *pm) { 
  movement = pm;
  return ErrorCode::Success;
}

ErrorCode Item::doMovement() {
  if (movement) {
    int cx = movement->getx();
    int cy = movement->gety();
    int cz = movement->getz();
    // Collision logic
    if (x == 79 && cx > 0) movement->reversex();
    if (x == 1 && cx < 0) movement->reversex();
    if (y == 24 && cy > 0) movement->reversey();
    if (y == 0 && cy < 0) movement->reversey();

    x += movement->getx(); 
    y += movement->gety();
    z += movement->getz();
  } else return ErrorCode::NoMovement;
  return ErrorCode::Success;
}

int Item::getX() const { return x; }

int Item::getY() const { return y; }

int Item::getZ() const { return z; }

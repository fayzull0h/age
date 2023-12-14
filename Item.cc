#include "Item.h"
#include "Movements.h"

Item::Item(int x, int y, int z): x{x}, y{y}, z{z}, ticksOffScreen{0}, 
  periodicMovement{nullptr} {}

int Item::getX() { return x; }

int Item::getY() { return y; }

int Item::getZ() { return z; }

ErrorCode Item::addMovement(Movement *m) {
  if (dynamic_cast<PeriodicMovement*>(m)) periodicMovement = dynamic_cast<PeriodicMovement*>(m);
  movements.emplace_back(m);
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

ErrorCode Item::tick(GameBoard *gb) {
  if (getTicks() > 10) return DeleteMe;
  if (periodicMovement) periodicMovement->move(gb, this);
  return doMovements(gb);
}

int Item::getTicks() const { return ticksOffScreen; }

ErrorCode Item::addTick() { 
  if (++ticksOffScreen > 10) return DeleteMe;
  else return NoMovement;
}

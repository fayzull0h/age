#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include "metadata.h"
#include "GameBoard.h"
#include "Item.h"
#include "Rectangle.h"
#include "Single.h"
#include "Bitmap.h"
#include <memory>

#define MAX_SPEED 3

enum MovementType {
  Up,
  Down,
  Right,
  Left,
  Periodic
};

class PeriodicMovement {
  std::vector<Item *> forms;
  int pos = 0;
  bool active = true;
 public:
  PeriodicMovement() {}
  ErrorCode addForm(Item *it) {
    if (it == nullptr) return BadRequest;
    if (dynamic_cast<Rectangle *>(it)) forms.emplace_back(new Rectangle{*(dynamic_cast<Rectangle *>(it))});
    else if (dynamic_cast<Single *>(it)) forms.emplace_back(new Single{*(dynamic_cast<Single *>(it))});
    else if (dynamic_cast<Bitmap *>(it)) forms.emplace_back(new Bitmap{*(dynamic_cast<Bitmap *>(it))});
    return Success;
  }
  MovementType getType() const { return MovementType::Periodic; }
  ErrorCode move() {
    if (active) {
      pos = (pos + 1) % (forms.size()+1);
    } else return NoMovement;
    return Success;
  }
  ErrorCode draw(WINDOW *Board) { return forms[pos-1]->draw(Board); }
  ErrorCode setActive(bool a) {
    active = a;
    return Success;
  }
  int getPos() const { return pos; }
};

/* Linear Movements */

class Movement final {
  MovementType t;
  int m;
 public:
  Movement(const MovementType &t, const int &m): t{t}, m{m} {
    if (m > MAX_SPEED || m < -MAX_SPEED) throw BadRequest;
  }
  int magnitude() const { return m; }
  MovementType getType() const { return t; }
};

#endif

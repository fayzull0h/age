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
  ErrorCode move(GameBoard *gb, Item *it) {
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

/** TO DeleTe
 * Linear Movement:
 * - can move Up, Down, Left, Right
 * - LinearMovement<Direction>(x)
 *    - x specifies how many units to move
 *    - a negative x specifies gravitation towards a side
class LinearMovement: public Movement {
  MovementType t;
 public:
  LinearMovement(int x): Movement{x} {}
  virtual MovementType __type() const = 0;
  MovementType getType() const override { return static_cast<T*>(this)->__type(); }
  ErrorCode move(GameBoard *gb, Item *it) override {
    if (m == 0) return DeleteMove;
    ErrorCode result = static_cast<T*>(this)->__move(gb, it);
    if (result == Success && m > 0) --m;
    return result;
  }
  
};

class Up: public LinearMovement<Up> {
  friend class LinearMovement;
  MovementType __type() const override { return MoveUp; }
  ErrorCode __move(GameBoard *gb, Item *it) {
    int height = it->getHeight(); 
    int y = it->getY();
    if (gb->boardtype == BoardType::Solid) {
      if (y > 1) {
        it->addY(-1);
        return Success;
      } else return NoMovement;
    } else {
      if (y + height > 0) {
        it->addY(-1);
        return Success;
      } else return it->addTick();
    }
  }
  
};

class Down: public LinearMovement<Down> {
  friend class LinearMovement;
  MovementType __type() const override { return MoveDown; }
  
  ErrorCode __move(GameBoard *gb, Item *it) {
    int height = it->getHeight();
    int y = it->getY();
    if (gb->boardtype == BoardType::Solid) {
      if (y + height < 24) {
        it->addY(1);
        return Success;
      } else return NoMovement;
    } else {
      if (y < 25) {
        it->addY(1);
        return Success;
      } else return it->addTick();
    }
  }
  
};

class Right: public LinearMovement<Right> {
  friend class LinearMovement;
  MovementType __type() const override { return MoveRight; }
  ErrorCode __move(GameBoard *gb, Item *it) {
    int width = it->getWidth();
    int x = it->getX();
    if (gb->boardtype == BoardType::Solid) {
      if (x + width < 79) {
        it->addX(1);
        return Success;
      } else return NoMovement;
    } else {
      if (x < 80) {
        it->addX(1);
        return Success;
      } else return it->addTick();
    }
  }
};

class Left: public LinearMovement<Left> {
  friend class LinearMovement;
  MovementType __type() const override { return MoveLeft; }
  ErrorCode __move(GameBoard *gb, Item *it) {
    int width = it->getWidth();
    int x = it->getX();
    if (gb->boardtype == BoardType::Solid) {
      if (x > 1) {
        it->addX(-1);
        return Success;
      } else return NoMovement;
    } else {
      if (x + width > 0) {
        it->addX(-1);
        return Success;
      } else return it->addTick();
    }
  }
};
*/

#endif

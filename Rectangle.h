#ifndef RECT_H
#define RECT_H

#include "Item.h"

template<typename T> class Rectangle: public Item {
  char c;
  int height, width;
 public:
  Rectangle(int x, int y, int z, int height, int width, char c): 
    Item{x, y, z}, c{c}, height{height}, width{width} {}

  ErrorCode draw(WINDOW *Board) override {
    return static_cast<T*>(this)->drawrect(Board);
  }

  ErrorCode doMovement() override {
    PeriodicMovement &m = getMovement();
    if (m.getx() == 0 && m.gety() == 0 && m.getz() == 0) return ErrorCode::NoMovement;
    int cx = m.getx();
    int cy = m.gety();
    //int cz = m->getz();

    if (getX() == 1 && cx < 0) cx = m.reversex();
    if (getX() == (79-width) && cx > 0) cx = m.reversex();
    if (getY() == 1 && cy < 0) cy = m.reversey();
    if (getY() == (24-height) && cy > 0) cy = m.reversey();

    addX(cx);
    addY(cy);
    // addZ(cz);
    return ErrorCode::Success;
  }

  char getChar() const { return c; }
  int getWidth() const { return width; }
  int getHeight() const { return height; }
};

class Hollow: public Rectangle<Hollow> {
  friend class Rectangle;
  ErrorCode drawrect(WINDOW *Board);
};

class Full: public Rectangle<Full> {
  friend class Rectangle;
  ErrorCode drawrect(WINDOW *Board);
};

#endif

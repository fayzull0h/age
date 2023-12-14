#ifndef LINE_MOVEMENT_H 
#define LINE_MOVEMENT_H

#include "Movement.h"

class LineMovement: public Movement {
  int changex, changey, changez;
 public:
  int getx() const { return changex; }
  int gety() const { return changey; }
  int getz() const { return changez; }
};

#endif

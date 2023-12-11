#ifndef PERIODIC_MOVEMENT_H
#define PERIODIC_MOVEMENT_H

#include <cstddef>

class PeriodicMovement {
  size_t period;
  int changex, changey, changez;
 public:
  PeriodicMovement(size_t period, int x, int y, int z): period{period}, changex{x},
  changey{y}, changez{z} {}
  size_t getperiod() const { return period; }
  int getx() const { return changex; }
  int gety() const { return changey; }
  int getz() const { return changez; }

  int reversex() { return (changex *= -1); }
  int reversey() { return (changey *= -1); }
  int reversez() { return (changez *= -1); }
};

#endif

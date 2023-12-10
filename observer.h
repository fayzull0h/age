#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "metadata.h"

template <typename InfoType, typename StateType> class Subject;

template <typename InfoType, typename StateType> class Observer {
 public:
  // pass the Subject that called the notify method
  virtual ErrorCode notify(Subject<InfoType, StateType> &whoFrom) = 0;
  virtual ~Observer() = default;
};
#endif

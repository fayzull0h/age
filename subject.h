#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <iostream>

/* A note on InfoType and StateType:

   We have separated the collection of fields into two parts:  its Info
   and its State.

   Info is for the parts of the subjject inherent to what it is:  its position
   and its colour.

   State is for the parts of the subject that, when changed, trigger
   notifications.  This is the information that the Observer "gets" when it
   calls getState on the subject.  It comprises the type of state, a direction,
   and a colour.  For more details, see metadata.h.
*/

template <typename InfoType, typename StateType> class Observer;

template <typename InfoType, typename StateType> class Subject {
  std::vector<Observer<InfoType, StateType>*> observers;
  StateType state;
 protected:
  void setState(StateType newS);
  int numObservers() const;
 public:
  void attach(Observer<InfoType, StateType> *o);  
  void notifyObservers();
  StateType getState() const;
};

template <typename InfoType, typename StateType>
int Subject<InfoType, StateType>::numObservers() const {
  return observers.size();
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attach(Observer<InfoType, StateType> *o) {
  observers.emplace_back(o);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::setState(StateType newS) { state = newS; }

template <typename InfoType, typename StateType>
StateType Subject<InfoType, StateType>::getState() const { return state; }
#endif

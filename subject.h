#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

template <typename InfoType, typename StateType> class Observer;

template <typename InfoType, typename StateType> class Subject {
  std::vector<Observer<InfoType, StateType>*> closeobservers;
  std::vector<Observer<InfoType, StateType>*> allobservers;
  StateType state;
 protected:
  void setState(StateType newS);
 public:
  void attachClose(Observer<InfoType, StateType> *o);  
  void attachAll(Observer<InfoType, StateType> *o);
  void notifyCloseObservers();
  void notifyAllObservers();
  virtual InfoType getInfo() const = 0;
  StateType getState() const;
};

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attachClose(Observer<InfoType, StateType> *o) {
  closeobservers.emplace_back(o);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attachAll(Observer<InfoType, StateType> *o) {
  allobservers.emplace_back(o);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyCloseObservers() {
  for (auto &ob : closeobservers) ob->notify(*this);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyAllObservers() {
  for (auto &ob : allobservers) ob->notify(*this);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::setState(StateType newS) { state = newS; }

template <typename InfoType, typename StateType>
StateType Subject<InfoType, StateType>::getState() const { return state; }

#endif

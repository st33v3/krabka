#ifndef TIMER_H
#define TIMER_H

#include "mode.h"
#include "common.h"

template<class T>
class Timer {
  public:
    Timer(T *owner);
    void loop();
    void stop();
    void start(unsigned long interval, void (*action)(T*));
    void postpone();
  protected:
  private:
    T* owner;
    bool stopped;
    void (*action)(T*);
    unsigned long interval;
    unsigned long last;
};

template<class T>
Timer<T>::Timer(T* o): owner(o) {
    stopped = true;
}

template<class T>
void Timer<T>::loop() {
    if (stopped) return;
    if (millis() - last > interval) {
        stopped = true;
        if (action) action(owner);
    } 
}

template<class T>
void Timer<T>::stop() {
    stopped = true;
}

template<class T>
void Timer<T>::start(unsigned long interval, void (*action)(T*)) {
    last = millis();
    this->interval = interval;
    this->action = action;
    stopped = false;
}

template<class T>
void Timer<T>::postpone() {
    last = millis();
}

#endif

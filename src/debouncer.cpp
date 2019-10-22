#include "debouncer.h"

Debouncer::Debouncer(pin_size_t p, int pe): pin(p), period(pe) {
}

void Debouncer::setup() {
  pinMode(pin, INPUT);
  last = millis();
  prev = digitalRead(pin) == HIGH;
}

void Debouncer::loop() {
  auto m = millis();
  bool s = digitalRead(pin) == HIGH;
  if (prev != s) {
    last = m;
    prev = s;
  }
}

bool Debouncer::ready() {
  return millis() - last > period;
}

bool Debouncer::state() {
  return prev;
}

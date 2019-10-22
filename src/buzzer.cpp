#include "buzzer.h"

Buzzer::Buzzer(pin_size_t p): pin(p) {

}

void Buzzer::setup() {
  pinMode(pin, OUTPUT);
  playing = false;
  digitalWrite(pin, LOW);
}

void Buzzer::loop() {
  if (!playing) return;
  auto m = micros();
  if (m - last > period) {
    state = !state;
    digitalWrite(pin, state ? HIGH : LOW);
    last = m;
  }
  if (m - start > duration) {
    stop();
    state = false;
    if (!next) {
      next();
    }
  }
}

void Buzzer::play(int freq, int dur, void (*next)(void)) {
  period = 1000000 / freq / 2;
  last = start = micros();
  digitalWrite(pin, HIGH);
  state = true;
  playing = true;
  duration = dur * 1000;
}

void Buzzer::stop() {
    playing = false;
    digitalWrite(pin, LOW);
}

bool Buzzer::isPlaying() {
  return playing;
}
#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
  private:
    pin_size_t pin;
    int period;
    unsigned long last;
    unsigned long duration;
    unsigned long start;
    bool state;
    bool playing;
    void (*next)(void);
  public:
  Buzzer(pin_size_t pin);
  void setup();
  void loop();
  void play(int freq, int dur, void (*next)(void));
  void stop();
  bool isPlaying();
};

#endif
#include "mode.h"
#include "common.h"

class WaitForButton : public Mode {
    public:
    virtual void enter();
    virtual void loop();
    virtual void setup();
    private:
    unsigned long start;
    int prevEnc;
};

static const int PROGMEM notes[] = {};

void WaitForButton::setup() {
    /**/
}

void WaitForButton::enter() {
  lightButtons(0);
  buzzer.stop();
  prevEnc = encoder = sizeof(notes)/2;
}


void WaitForButton::loop() {
  if (encoder != prevEnc && !buzzer.isPlaying()) {
    if (encoder < 0) encoder = 0;
    if (encoder >= sizeof(notes)) encoder = sizeof(notes) - 1;
    prevEnc = encoder;
    buzzer.play(notes[encoder], 200, NULL);
  }
}

static WaitForButton inst;
Mode &modeWaitForButton = inst;
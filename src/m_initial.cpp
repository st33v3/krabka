#include "mode.h"
#include "common.h"

class Initial : public Mode {
    public:
    virtual void enter();
    virtual void loop();
    virtual void setup();
    private:
    unsigned long start;
};


void Initial::setup() {
    /**/
}

void Initial::enter() {
  start = millis();
  lightButtons(7);
  rgbLight(0, 0, 0);
  buzzer.stop();
}


void Initial::loop() {
  if (millis() - start > 1000) {
    setMode(modeWaitForButton);
  }
}

static Initial inst;
Mode &modeInitial = inst;
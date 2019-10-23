#include "mode.h"
#include "common.h"
#include "notes.h"

class WaitForButton : public Mode {
    public:
    virtual void enter();
    virtual void loop();
    virtual void setup();
    private:
    int prevBtn;
    int prevEnc;
};

static const int PROGMEM notes[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5};

void WaitForButton::setup() {
    /**/
}

void WaitForButton::enter() {
  lightButtons(0);
  buzzer.stop();
  rgbLight(0, 0, 0);
  prevEnc = encoder = sizeof(notes)/2;
  prevBtn = 0;
}


void WaitForButton::loop() {
  if (encoder != prevEnc && !buzzer.isPlaying()) {
    if (encoder < 0) encoder = 0;
    if (encoder >= sizeof(notes)) encoder = sizeof(notes) - 1;
    prevEnc = encoder;
    buzzer.play(notes[encoder], 200, NULL);
  }
  int btns = getButtons();
  if (prevBtn != btns) {
    lightButtons(btns);
    if (prevBtn && !btns) setMode(modeFollowButtons);
    prevBtn = btns;
  }
}

static WaitForButton inst;
Mode &modeWaitForButton = inst;
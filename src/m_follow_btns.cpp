#include "mode.h"
#include "common.h"
#include "m_light_enc.h"
#include "timer.h"

class FollowButtons : public EncoderLight {
  public:
    FollowButtons();
    virtual void enter();
    virtual void loop();
    virtual void setup();
  private:
    Timer<FollowButtons> pauseTimer;
    Timer<FollowButtons> resetTimer;
    void nextButton();
    int expectBtn;
    int lastBtns;
};

FollowButtons::FollowButtons(): pauseTimer(this), resetTimer(this) {

}

void FollowButtons::setup() {
    /**/
}

void FollowButtons::enter() {
  expectBtn = 0;
  lastBtns = 0;
  lightButtons(0);
  pauseTimer.start(500, [](FollowButtons* ow){ ow->nextButton(); });
  resetTimer.start(2000, [](FollowButtons* ow){ setMode(modeWaitForButton); });
  buzzer.stop();
  randomSeed(millis());
  EncoderLight::enter();
  setLevel(0);
}


void FollowButtons::loop() {
  if (expectBtn) {
    int btns = getButtons();
    if (btns >= 0 && btns != lastBtns) {
      resetTimer.postpone();
      if (!btns && lastBtns == expectBtn) {
        lightButtons(0);
        expectBtn = 0;
        int l = getLevel();
        if (l < 5) l++;
        setLevel(l);
        pauseTimer.start(500, [](FollowButtons* ow){ ow->nextButton(); });
      }
    }
  }
  pauseTimer.loop();
  EncoderLight::loop();
}

void FollowButtons::nextButton() {
  expectBtn = 1 << random(0, 3);
  lightButtons(expectBtn);
}

static FollowButtons inst;
Mode &modeFollowButtons = inst;
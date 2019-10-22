#include "common.h"
#include "debouncer.h"
#include "buzzer.h"

Debouncer button1(3, 50), button2(4, 50), button3(7, 50), encA(10, 10), encB(11, 10);
Buzzer buzzer(8);

Mode* mode = NULL;

void setMode(Mode &newMode) {
  mode = &newMode;
  mode -> enter();
}

int getButtons() {
  if (!button1.ready() || !button2.ready() || !button3.ready()) return 0;
  return 
    button1.state() ? 1 : 0 +
    button2.state() ? 2 : 0 +
    button3.state() ? 4 : 0;
}

void lightButtons(int mask) {
  digitalWrite(1, mask & 1 ? HIGH : LOW);
  digitalWrite(2, mask & 2 ? HIGH : LOW);
  digitalWrite(3, mask & 4 ? HIGH : LOW);
}

void toInitial();
void toWaitForButton();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  button1.setup();
  button2.setup();
  button3.setup();
  buzzer.setup();
  encA.setup();
  encB.setup();
  modeInitial.setup();
  modeWaitForButton.setup();
  setMode(modeInitial);
}

int encoder = 0;
int encData[] = {0, 1, 3, 2};
int lastEnc = 0;

void loop() {
  button1.loop();
  button2.loop();
  button3.loop();
  buzzer.loop();
  encA.loop();
  encB.loop();
  if (encA.ready() && encB.ready()) {
    int e = encA.state() ? 1 : 0 | encB.state() ? 2 : 0;
    if (e == encData[(lastEnc - 1) & 3]) encoder--;
    if (e == encData[(lastEnc + 1) & 3]) encoder++;
    for (int i=0; i<4; i++) if (encData[i] == e) lastEnc = i;
  }
  if (mode) mode->loop();
}

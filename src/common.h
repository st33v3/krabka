#ifndef MY_COMMON_H
#define MY_COMMON_H

#include <Arduino.h>
#include "mode.h"
#include "buzzer.h"

extern int encoder;

void setMode(Mode &mode);
int getButtons();
void lightButtons(int mask);

extern Buzzer buzzer;

extern Mode &modeInitial;
extern Mode &modeWaitForButton;
#endif

#ifndef MY_COMMON_H
#define MY_COMMON_H

#include <Arduino.h>
#include "mode.h"
#include "buzzer.h"

extern int encoder;

void setMode(Mode &mode);
int getButtons();
void lightButtons(int mask);
void rgbLight(int r, int g, int b);

/*
 * hue - 0 .. 360
 * sat - 0 .. 1
 * bright 0 .. 1
 */ 
void hsbToRgb(float hue, float sat, float bright, int &r, int& g, int& b);
extern Buzzer buzzer;

extern Mode &modeInitial;
extern Mode &modeWaitForButton;
extern Mode &modeFollowButtons;

#endif

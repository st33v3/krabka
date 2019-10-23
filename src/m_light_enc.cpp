#include "m_light_enc.h"

EncoderLight::EncoderLight() {
  /**/
}

void EncoderLight::enter() {
  encoder = 0;
}


void EncoderLight::loop() {
  if (encoder != 0) {
    setHue(hue + encoder);
    encoder = 0;
  }
}

void EncoderLight::setLevel(int l) {
  level = min(max(l, 0), 5);
  setRGB();
}

void EncoderLight::setHue(int h) {
  hue = h;
  if (hue > 359) hue = hue - 360;
  if (hue < 0) hue = 360 - hue;
  setRGB();
}

int EncoderLight::getLevel() {
  return level;
}

int EncoderLight::getHue() {
  return hue;
}

void EncoderLight::setRGB() {
  int r, g, b;
  hsbToRgb(getHue(), 1.0, ((float) getLevel()) / 5.0, r, g, b);
  rgbLight(r, g, b);
}

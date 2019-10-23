#include "common.h"
#include "debouncer.h"
#include "buzzer.h"

#define PIN_BTN1 1
#define PIN_BTN2 1
#define PIN_BTN3 1

#define PIN_BTN1_LED 2
#define PIN_BTN2_LED 2
#define PIN_BTN3_LED 2

#define PIN_LIGHT_R 3
#define PIN_LIGHT_G 3
#define PIN_LIGHT_B 3

#define PIN_BUZZER 4

#define PIN_ENC_A 5
#define PIN_ENC_B 5

Debouncer button1(PIN_BTN1, 50), button2(PIN_BTN2, 50), button3(PIN_BTN3, 50), encA(PIN_ENC_A, 10), encB(PIN_ENC_B, 10);
Buzzer buzzer(PIN_BUZZER);

Mode* mode = NULL;

void setMode(Mode &newMode) {
  mode = &newMode;
  mode -> enter();
}

int getButtons() {
  if (!button1.ready() || !button2.ready() || !button3.ready()) return -1 && ~7;
  return 
    button1.state() ? 1 : 0 |
    button2.state() ? 2 : 0 |
    button3.state() ? 4 : 0;
}

void lightButtons(int mask) {
  digitalWrite(PIN_BTN1_LED, mask & 1 ? HIGH : LOW);
  digitalWrite(PIN_BTN2_LED, mask & 2 ? HIGH : LOW);
  digitalWrite(PIN_BTN3_LED, mask & 4 ? HIGH : LOW);
}

void rgbLight(int r, int g, int b) {
  analogWrite(PIN_LIGHT_R, r);
  analogWrite(PIN_LIGHT_G, g);
  analogWrite(PIN_LIGHT_B, b);
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

static int color(float c) {
  c = min(max(c, 0), 1);
  return (int)(c * 255.0);
}

void hsbToRgb(float hue, float sat, float bright, int &r, int& g, int& b) {
  int i;
	float f, p, q, t;
	if( sat == 0 ) {
		// achromatic (grey)
		r = g = b = color(bright);
		return;
	}
	hue /= 60.0;			// sector 0 to 5
	i = floor( hue );
	f = hue - i;			// factorial part of h
	p = bright * ( 1.0 - sat );
	q = bright * ( 1.0 - sat * f );
	t = bright * ( 1.0 - sat * ( 1.0 - f ) );
	switch( i ) {
		case 0:
			r = color(bright);
			g = color(t);
			b = color(p);
			break;
		case 1:
			r = color(q);
			g = color(bright);
			b = color(p);
			break;
		case 2:
			r = color(p);
			g = color(bright);
			b = color(t);
			break;
		case 3:
			r = color(p);
			g = color(q);
			b = color(bright);
			break;
		case 4:
			r = color(t);
			g = color(p);
			b = color(bright);
			break;
		default:		// case 5:
			r = color(bright);
			g = color(p);
			b = color(q);
			break;
	}
}
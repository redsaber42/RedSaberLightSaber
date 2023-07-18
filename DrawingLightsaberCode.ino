#include <FastLED.h>
#include <EEPROM.h>

#define BUTTON_PIN  4
#define LED_PIN     3

#define BRIGHTNESS  64
#define NUM_LEDS    265
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
bool activated = false;
int ledsPerFrame = 1;
bool buttonDown = false;

float r = 255;
float g = 255;
float b = 0;


void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  
  unsigned int off[3] = { 0, 0, 0 };
  setWholeSaberToColor(off);
  
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
    int buttonState = digitalRead(BUTTON_PIN);

    if (!buttonDown && buttonState == HIGH){
      if (activated) {
          DeactivateSaber();
      }
      else {
          ActivateSaber();
      }
    }
  
    buttonDown = buttonState == HIGH;
}


void setWholeSaberToColor(unsigned int color[3]) {
    for (int led = 0; led < NUM_LEDS; led++) {
      leds[led] = CRGB( color[0], color[1], color[2]);
    }
    FastLED.show();
}

void ActivateSaber() {
  for (int led = 0; led <= NUM_LEDS / 2; led += ledsPerFrame) {
      for (int i = 0; i <= led; i++) {
          leds[i] = CRGB(r, g, b);
          leds[NUM_LEDS-i] = CRGB(r, g, b);
      }
      FastLED.show();
  }
  activated = true;
}

void DeactivateSaber() {
  for (int led = 0; led <= NUM_LEDS / 2; led += ledsPerFrame) {
      for (int i = 0; i <= led; i++) {
          leds[NUM_LEDS/2-i] = CRGB(0, 0, 0);
          leds[NUM_LEDS/2+i] = CRGB(0, 0, 0);
      }
      FastLED.show();
  }
  activated = false;
}

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

float r = 255;
float g = 255;
float b = 0;

short doublePressMaxTime = 250;
unsigned int timePress = 0;
unsigned int timePressLimit = 0;
short clicks = 0;

bool changing = false;



void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  if (!(EEPROM.read(0) == 0 && EEPROM.read(1) == 0 && EEPROM.read(2) == 0)) {
    r = EEPROM.read(0);
    g = EEPROM.read(1);
    b = EEPROM.read(2);
  }
  
  unsigned int off[3] = { 0, 0, 0 };
  setWholeSaberToColor(off);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
    int buttonState = digitalRead(BUTTON_PIN);

    if (buttonState == LOW) {
      delay(200);
      
      if (clicks == 0) {
        timePress = millis();
        timePressLimit = timePress + doublePressMaxTime;    
        clicks = 1;
      }

      else if (clicks == 1 && millis() < timePressLimit){
        changing = true;

        timePress = 0;
        timePressLimit = 0;
        clicks = 0;      
      }    
    }

    if (clicks == 1 && timePressLimit != 0 && millis() > timePressLimit){
      if (activated) {
          DeactivateSaber();
      }
      else {
          ActivateSaber();
      }
      
      timePress = 0;
      timePressLimit = 0;
      clicks = 0;
    }

    if (activated && changing) {
        unsigned int rgbColor[3];
    
        rgbColor[0] = 255;
        rgbColor[1] = 0;
        rgbColor[2] = 0;
      
        for (int decColor = 0; decColor < 3; decColor += 1) {
          int incColor = decColor == 2 ? 0 : decColor + 1;
      
          for(int i = 0; i < 255; i += 1) {
            rgbColor[decColor] -= 1;
            rgbColor[incColor] += 1;
            
            
            if (digitalRead(BUTTON_PIN) == LOW) {
              r = rgbColor[0];
              g = rgbColor[1];
              b = rgbColor[2];

              EEPROM.write(0, r);
              EEPROM.write(1, g);
              EEPROM.write(2, b);

              changing = false;
              timePress = 0;
              timePressLimit = 0;
              clicks = 5;
              activated = true;
              return;
            }

            setWholeSaberToColor(rgbColor);
            delay(10);
          }
        }
    }
    
    if (clicks >= 2) {
      clicks = 0;
    }
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
  changing = false;
  timePress = 0;
  timePressLimit = 0;
  clicks = 0;
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

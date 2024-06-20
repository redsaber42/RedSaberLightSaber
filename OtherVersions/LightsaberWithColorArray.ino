#include <FastLED.h>
#include <EEPROM.h>

// CHANGE these to whatever pins you've connected the LED and BUTTON to
#define BUTTON_PIN  4
#define LED_PIN     3

// CHANGE this for your desired brightness (0-255)
#define BRIGHTNESS  64
// CHANGE this for the number of LEDs you have connected
#define NUM_LEDS    265
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB


CRGB leds[NUM_LEDS];
bool activated = false;
int ledsPerFrame = 1; // This changes the speed the lightsaber goes out at, so if you want it to draw faster, increase this number

/* HERE ARE THE COLOR SWITCHING VARIABLES */
// ADD/REMOVE colors from this array to change what color options you have
CRGB colorOptions[] = {CRGB(255,0,0), CRGB(0,255,255), CRGB(255,155,0), CRGB(255,0,255), CRGB(255,30,0), CRGB(255,40,40), CRGB(0,255,0), CRGB(255,255,255)};
// UPDATE this variable to the number of options in this array ^^^ so the code doesn't break
int numColorOptions = 8;
int colorIndex = 0;

// If you press the button twice within this time it counts as a double click  (in milliseconds)
// So if you set it to 500, that would mean you could have up to half a second in between clicks and it will still count as a double click
short doublePressMaxTime = 250; 
unsigned int timePress = 0;
unsigned int timePressLimit = 0;
short clicks = 0;


// THIS code runs once when the Arduino boots up
void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // Load the selected color from memory (if it is valid)
  // If there's 'nothing' stored in an EEPROM slot, it will simply be 0
  if (EEPROM.read(0) < numColorOptions) {
    colorIndex = EEPROM.read(0);
  }
  
  // Start the saber as off, then the user can activate it
  CRGB off = CRGB(0,0,0);
  setWholeSaberToColor(off);
  
  pinMode(BUTTON_PIN, INPUT);
}

// This code will run over and over again, as long as the Arduino is on
void loop() {
    int buttonState = digitalRead(BUTTON_PIN);
    pinMode(BUTTON_PIN, OUTPUT);
    digitalWrite(BUTTON_PIN, LOW);

    if (buttonState == HIGH){
      delay(200);
      
      if (clicks == 0) {
        timePress = millis();
        timePressLimit = timePress + doublePressMaxTime;    
        clicks = 1;
      }

      else if (clicks == 1 && millis() < timePressLimit) {
        // IF WE GET HERE that means we've registered a double click
        
        // So we increase the colorIndex (while keeping it in bounds)
        colorIndex++;
        if (colorIndex >= numColorOptions) {
          colorIndex = 0;
        }

        // Change the saber to that color (if the saber is on)
        if (activated) {
          setWholeSaberToColor(colorOptions[colorIndex]);
        }

        // Save that color
        EEPROM.write(0, colorIndex);

        // And we reset these variables so we can go back to looking for clicks
        timePress = 0;
        timePressLimit = 0;
        clicks = 0;      
      }    
    }

    if (clicks == 1 && timePressLimit != 0 && millis() > timePressLimit) {
      // IF WE GET HERE it means we pressed the button once and then waited for the set amount of time, and no double click was registered
      
      // So we switch whether the saber is on or off
      if (activated) {
          DeactivateSaber();
      }
      else {
          ActivateSaber();
      }
      
      // And we reset these variables so we can go back to looking for clicks
      timePress = 0;
      timePressLimit = 0;
      clicks = 0;
    }
    
    if (clicks >= 2) {
      clicks = 0;
    }
}

// Loop over all of the LEDs on the lightsaber and set them to the input color
void setWholeSaberToColor(CRGB color) {
    for (int led = 0; led < NUM_LEDS; led++) {
        leds[led] = color;
    }
    FastLED.show();
}

// Loop over all the LEDs in the saber, but each time we run the loop, we'll only turn on the LEDs up to a certain point
// So we get the effect of the lightsaber coming on 1 pixel at a time
void ActivateSaber() {
  for (int led = 1; led <= NUM_LEDS / 2; led += ledsPerFrame) {
      for (int i = 1; i <= led; i++) {
          // Since it's 2 LED strips and the tip is in the middle, we have to turn on 2 pixels, one on each side of the blade

          // Set the current LED to white
          leds[i] = CRGB(255,255,255);
          leds[NUM_LEDS-i] = CRGB(255,255,255);

          // Set the last LED to the proper color
          leds[i] = colorOptions[colorIndex];
          leds[NUM_LEDS-i] = colorOptions[colorIndex];
      }
      FastLED.show();
  }

  activated = true;
  // Update these variables so we are ready to look for clicks or double clicks
  timePress = 0;
  timePressLimit = 0;
  clicks = 0;
}

// Loop over all the LEDs in the saber, but each time we run the loop, we'll turn off the LEDs from the tip down to a certain point
// So we get the effect of the lightsaber turning off 1 pixel at a time
void DeactivateSaber() {
  for (int led = 0; led <= NUM_LEDS / 2; led += ledsPerFrame) {
      for (int i = 0; i <= led; i++) {
          // Since it's 2 LED strips and the tip is in the middle, we have to turn off 2 pixels, one on each side of the blade
          leds[NUM_LEDS/2-i] = CRGB(0, 0, 0);
          leds[NUM_LEDS/2+i] = CRGB(0, 0, 0);
      }
      FastLED.show();
  }
  activated = false;
}

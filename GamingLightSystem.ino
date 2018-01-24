/**
 * Arduino Powered Lighting Control System
 * This Program Allows An Arduino To Control
 * NeoPixel LEDs, And Have Their Color Gradually
 * Change Over Time To Create a Pulsing Effect.
 * 
 * Author: Cody R.
 * 
 */


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

//Initial Configuratio

/*
   User Configuration:
*/
#define PIN 6 // Data Pin Being Used
#define NUMPIXELS 16 // Number of LEDs Connected
int delayval = 300; // Delay Between Lighting Updates
int originalColor[3] = {220, 80, 80}; // Default Display Color, Inputted In The Form {R, G, B} With Values From 0-255.
int delta[3] = {30, 30, 30}; // Maximum Variation From Original Color (Out of 255)



Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); // Configures LEDs as Neopixels
int currentColor[3]; // Current Color Values Being Displayed. Do Not Edit This Manually.
bool increasing[3] = {true, true, true}; // Determines If Color Value is Increasing or Decreasing. Do Not Edit This Manually.

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.

  //Sets RGB Values To The Original Color
  currentColor[0] = originalColor[0];
  currentColor[1] = originalColor[1];
  currentColor[2] = originalColor[2];
}

void loop() {

  bool colorBeingChanged[3] = {true, false, false}; //Which Color Is Being Changes (Red, Green, Blue)

  for (int i = 0; i < 3; i++)
  {
    if (colorBeingChanged[i]) //Will Only Run This Loop If The Color Should Be Changed
    {
      if (increasing[i] && currentColor[i] < 255 && abs(currentColor[i] - originalColor[i]) < delta[i])
      {
        currentColor[i]++; //Increase Displayed Color Value
      }
      else if (!increasing[i] && currentColor[i] > 0 && abs(currentColor[i] - originalColor[i]) < delta[i])
      {
        currentColor[i]--; //Decrease Displayed Color Value
      }
      else
      {
        increasing[i] = !increasing[i]; //Change Direction of Colors
      }
    }
  }


  //Address All of the Connected LEDs
  for (int i = 0; i < NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color(currentColor[0], currentColor[1], currentColor[2]));
    pixels.show(); //Update LEDs
    delay(delayval); //Delay Between Loops
  }
}

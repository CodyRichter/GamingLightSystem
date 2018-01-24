/**
   Arduino Powered Lighting Control System
   This Program Allows An Arduino To Control
   NeoPixel LEDs, And Have Their Color Gradually
   Change Over Time To Create a Pulsing Effect.

   Author: Cody R.

*/


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

/*
   User Configuration:
*/
#define PIN 13 // Data Pin Being Used.
#define NUMPIXELS 4 // Number of LEDs Connected.
const int delayval = 10; // Delay Between Lighting Updates.
const int originalColor[3] = {100, 255, 0}; // Default Display Color, Inputted In The Form {G, R, B} With Values From 0-255.
const int delta[3] = {100, 100, 100}; // Maximum Variation From Original Color (Out of 255).


//Program Variables. Do Not Edit Manually.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800); // Configures LEDs as Neopixels.
int currentColor[3]; // Current Color Values Being Displayed.
bool increasing[3] = {true, true, true}; // Determines If Color Value is Increasing or Decreasing.

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.

  //Sets GRB Values To The Original Color
  currentColor[0] = originalColor[0];
  currentColor[1] = originalColor[1];
  currentColor[2] = originalColor[2];

  pixels.setBrightness(255);

  pixels.show();
}

void loop() {

  bool colorBeingChanged[3] = {true, false, false}; //Which Color Is Being Changed (Red, Green, Blue)

  for (int i = 0; i < 3; i++)
  {
    //The Variable "i" corresponds to the color being changed, with 0=red, 1=green, and 2=blue.
    if (colorBeingChanged[i]) //Will Only Run This Loop If The Color Should Be Changed
    {
      if (increasing[i] && currentColor[i] < 255 && abs(currentColor[i] - originalColor[i]) < delta[i])
      {
        currentColor[i]++; //Increment Displayed Color Value
      }
      else if (!increasing[i] && currentColor[i] > 0 && abs(currentColor[i] - originalColor[i]) < delta[i])
      {
        currentColor[i]--; //Decrement Displayed Color Value
      }
      else if (currentColor[i] - originalColor[i] > 0)
      {
        increasing[i] = !increasing[i]; //Change Direction of Color
        currentColor[i] -= 3;
      }
      else
      {
        increasing[i] = !increasing[i]; //Change Direction of Color
        currentColor[i] += 3;
      }
    }
  }


  //Address All of the Connected LEDs
  for (int i = 0; i < NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color(currentColor[0], currentColor[1], currentColor[2]));
    //pixels.setPixelColor(i, currentColor[0], currentColor[1], currentColor[2]);
    pixels.show(); //Update LEDs
    delay(delayval); //Delay Between Loops
  }
}

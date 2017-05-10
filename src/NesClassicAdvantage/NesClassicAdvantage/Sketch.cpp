/*
* Nintendo Classic Advantage Controller - Nintendo Advantage inspired 
* controller for the NES Classic Mini!
* Copyright (c) 2017 bbtinkerer
* 
* Based off of Wii RetroPad Adapter by Bruno Freitas - 
* https://github.com/bootsector/wii-retropad-adapter
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*Beginning of Auto generated code by Atmel studio */
#include <Arduino.h>
/*End of auto generated code by Atmel studio */

#include "WMExtension.h"
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio

// controller buttons
// pin numbers according to Arduino pin numbering
#define LEFT_BUTTON_PIN 2
#define RIGHT_BUTTON_PIN 3
#define UP_BUTTON_PIN 4
#define DOWN_BUTTON_PIN 5
#define A_BUTTON_PIN 6
#define B_BUTTON_PIN 7
#define MINUS_BUTTON_PIN 10
#define PLUS_BUTTON_PIN 11
#define HOME_BUTTON_PIN 12

// turbo controls
#define TURBO_SWITCH_A_PIN 0
#define TURBO_SWITCH_B_PIN 1
#define TURBO_POT_A_PIN 0 // analog pin
#define TURBO_POT_B_PIN 1
#define TURBO_LED_A_PIN 8
#define TURBO_LED_B_PIN 9
#define MAX_TURBO_RATE 34 // HZ, -1 for max since adding 1 in code so no 0HZ

// Classic Controller Buttons
int bdl = 0; // D-Pad Left state
int bdr = 0; // D-Pad Right state
int bdu = 0; // D-Pad Up state
int bdd = 0; // D-Pad Down state
int ba = 0; // A button state
int bb = 0; // B button state
int bx = 0; // X button state
int by = 0; // Y button state
int bl = 0; // L button state
int br = 0; // R button state
int bm = 0; // MINUS button state
int bp = 0; // PLUS button state
int bhome = 0; // HOME button state
int bzl = 0; // ZL button state
int bzr = 0; // ZR button state
int lt = 0; // L analog value
int rt = 0; // R analog value

// Analog Buttons
byte lx = WMExtension::get_calibration_byte(2);
byte ly = WMExtension::get_calibration_byte(5);
byte rx = WMExtension::get_calibration_byte(8);
byte ry = WMExtension::get_calibration_byte(11);

// turbo variables
int enableTurboA = 1;
int potAVal = 0;
int turboRateA = 1;
long turboTimeA = 0;
long runningTurboTimeA = 0;
bool turboPressedA = false;
long turboAOnTime = 0;
long turboAResetTime = 0;

int enableTurboB = 1;
int potBVal = 0;
int turboRateB = 1;
long turboTimeB = 0;
long runningTurboTimeB = 0;
bool turboPressedB = false;
long turboBOnTime = 0;
long turboBResetTime = 0;

void performTurboAction(int enableTurbo, int *button, long *turboOnTime, long *turboResetTime,
   bool *turboPressed, long *turboTime, long *runningTurboTime, int turboPotPin, int turboLedPin);

void setup() {
   // Set PushButton pins as input, turning pull-up on
   pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
   pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);
   pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
   pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
   pinMode(A_BUTTON_PIN, INPUT_PULLUP);
   pinMode(B_BUTTON_PIN, INPUT_PULLUP);
   pinMode(MINUS_BUTTON_PIN, INPUT_PULLUP);
   pinMode(PLUS_BUTTON_PIN, INPUT_PULLUP);
   pinMode(HOME_BUTTON_PIN, INPUT_PULLUP);
   pinMode(TURBO_SWITCH_A_PIN, INPUT_PULLUP);
   
   pinMode(TURBO_LED_A_PIN, OUTPUT);
   pinMode(TURBO_LED_B_PIN, OUTPUT);
   digitalWrite(TURBO_LED_A_PIN, LOW);
   digitalWrite(TURBO_LED_B_PIN, LOW);
   
   digitalWrite(LEFT_BUTTON_PIN, HIGH);
   digitalWrite(RIGHT_BUTTON_PIN, HIGH);
   digitalWrite(UP_BUTTON_PIN, HIGH);
   digitalWrite(DOWN_BUTTON_PIN, HIGH);
   digitalWrite(A_BUTTON_PIN, HIGH);
   digitalWrite(B_BUTTON_PIN, HIGH);
   digitalWrite(MINUS_BUTTON_PIN, HIGH);
   digitalWrite(PLUS_BUTTON_PIN, HIGH);
   digitalWrite(HOME_BUTTON_PIN, HIGH);
   digitalWrite(TURBO_SWITCH_A_PIN, HIGH);
   digitalWrite(TURBO_SWITCH_B_PIN, HIGH);
   
   // Prepare wiimote communications
   WMExtension::init();
}

void loop() {
   bdl = !digitalRead(LEFT_BUTTON_PIN);
   bdr = !digitalRead(RIGHT_BUTTON_PIN);
   bdu = !digitalRead(UP_BUTTON_PIN);
   bdd = !digitalRead(DOWN_BUTTON_PIN);
   ba = !digitalRead(A_BUTTON_PIN);
   bb = !digitalRead(B_BUTTON_PIN);
   bm = !digitalRead(MINUS_BUTTON_PIN);
   bp = !digitalRead(PLUS_BUTTON_PIN);
   bhome = !digitalRead(HOME_BUTTON_PIN);
   enableTurboA = !digitalRead(TURBO_SWITCH_A_PIN);
   enableTurboB = !digitalRead(TURBO_SWITCH_B_PIN);

   performTurboAction(enableTurboA, &ba, &turboAOnTime, &turboAResetTime, &turboPressedA, &turboTimeA, &runningTurboTimeA, TURBO_POT_A_PIN, TURBO_LED_A_PIN);
   performTurboAction(enableTurboB, &bb, &turboBOnTime, &turboBResetTime, &turboPressedB, &turboTimeB, &runningTurboTimeB, TURBO_POT_B_PIN, TURBO_LED_B_PIN);

   WMExtension::set_button_data(bdl, bdr, bdu, bdd, ba, bb, bx, by, bl, br,
   bm, bp, bhome, lx, ly, rx, ry, bzl, bzr, lt, rt);
}


void performTurboAction(int enableTurbo, int *button, long *turboOnTime, long *turboResetTime, 
   bool *turboPressed, long *turboTime, long *runningTurboTime, int turboPotPin, int turboLedPin)
{
   int potValue = 0;
   
   if(enableTurbo && *button)
   {
      // set rate of turbo based on the pot
      // 500 - milliseconds time button-on when turbo is set to 1HZ (half second on, half second off)
      // dividing 500 by the ratio of the pot to the max turbo rate gives how long the button should be pressed on
      potValue = analogRead(turboPotPin) + 1.0;
      *turboOnTime = 500 / (potValue / 1024.0 * MAX_TURBO_RATE + 1);
         
      // double the on-time is when the timer should reset
      *turboResetTime = *turboOnTime * 2;
      
      // checked to see if first press of the button
      if(!*turboPressed)
      {
         //  first time pressed so take note of time, reset the running time and change state that the button is pressed down
         *turboTime = millis();
         *runningTurboTime = 0;
         *turboPressed = true;
      }
      else
      {
         // button was already pressed from before, take note of the time passed since first pressed
         *runningTurboTime = millis() - *turboTime;
      }
      
      // check the running time against how long the button should be pressed 
      if(*runningTurboTime < *turboOnTime)
      {
         // status to show that button currently pressed
         digitalWrite(turboLedPin, HIGH);
      }
      else
      {
         // running time is past when the button should be held down,
         // virtually unpress the button
         *button = 0;
         
         // status to show the button is unpressed
         digitalWrite(turboLedPin, LOW);
         
         if(*runningTurboTime > *turboResetTime)
         {
            // past the time that the button should be virtually unpressed
            // reset so the button is signaled as pressed again
            *turboPressed = false;
         }
      }
   }
   else
   {
      // need to reset just in case was left on from a previous turbo operation when turbo no longer enabled
      digitalWrite(turboLedPin, LOW);
      *turboPressed = false;
   }
}



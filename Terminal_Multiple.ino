//  Reads an analog input on pin A0, prints the result to the Serial Monitor.
//  The sensor gain is controlled by the program.
//  Graphical representation is available using Elemyo_GUI, Python_GUI and Matlab_GUI.
//  2021-03-19 by ELEMYO (https://github.com/ELEMYO/Elemyo-library)
//
//  Changelog:
//  2021-03-19 - initial release

/* ============================================
ELEMYO library code is placed under the MIT license
Copyright (c) 2018 ELEMYO

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================


Wiring the ELEMYO sensor to an ESP32

ELEMYO -->  ESP32
  +        5V
  -        GND
  OUT1     pin 25
  СS       pin 10
  MOSI     pin 11 
  SCK      pin 13

*/


#include <ELEMYO.h>

#define   CSpin1         10
#define   CSpin2         9
#define   CSpin3         8
#define   CSpin4         7

#define   sensorInPin1   A0      // analog input pin that the sensor is attached to
#define   sensorInPin2   A1      // analog input pin that the sensor is attached to
#define   sensorInPin3   A2      // analog input pin that the sensor is attached to
#define   sensorInPin4   A3      // analog input pin that the sensor is attached to

#define   timePeriod    0.7     // frequency of signal update (time in ms).

ELEMYO MyoSensor1(CSpin1);
ELEMYO MyoSensor2(CSpin2);
ELEMYO MyoSensor3(CSpin3);
ELEMYO MyoSensor4(CSpin4);

void setup() {
  
  Serial.begin(115200);           // initialize serial communications at 115200 bps:
  MyoSensor1.gain(1);              // Initial value of gain
  MyoSensor2.gain(1);              // Initial value of gain
  MyoSensor3.gain(1);              // Initial value of gain
  MyoSensor4.gain(1);              // Initial value of gain
  pinMode(sensorInPin1, INPUT);    // initialize sensorInPin
  pinMode(sensorInPin2, INPUT);    // initialize sensorInPin
  pinMode(sensorInPin3, INPUT);    // initialize sensorInPin
  pinMode(sensorInPin4, INPUT);    // initialize sensorInPin
}

void loop() {
  Serial.print(analogRead(sensorInPin1));               // print the results to the Serial Monitor:
  Serial.print(" ");
  Serial.print(analogRead(sensorInPin2));               // print the results to the Serial Monitor:
  Serial.print(" ");
  Serial.print(analogRead(sensorInPin3));               // print the results to the Serial Monitor:
  Serial.print(" ");
  Serial.println(analogRead(sensorInPin4));             // print the results to the Serial Monitor:
  
  delayMicroseconds(timePeriod*1000);       // wait before the next loop
}

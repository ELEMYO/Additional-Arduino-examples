// Actuator control algorithm by flexor and extensor muscle signals
// 2020-11-12 by ELEMYO (https://github.com/ELEMYO/Elemyo-library)
//
// Changelog:
//     2020-11-12 - initial release

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


Wiring the ELEMYO sensor to an Arduino

1th Sensor -->  Arduino
  +        5V
  -        GND
  S        A0
  СS       pin 10 (SS pin)
  MOSI     pin 11 (UNO, Nano, Mini), pin 51 (Mega), pin SI (Leonardo), pin 16 (Pro micro)
  SCK      pin 13 (UNO, Nano, Mini), pin 52 (Mega), pin SCK (Leonardo), pin 15 (Pro micro)

2nd Sensor -->  Arduino
  +        5V
  -        GND
  S        A1
  СS       pin 9 (SS pin)
  MOSI     pin 11 (UNO, Nano, Mini), pin 51 (Mega), pin SI (Leonardo), pin 16 (Pro micro)
  SCK      pin 13 (UNO, Nano, Mini), pin 52 (Mega), pin SCK (Leonardo), pin 15 (Pro micro)

*/

#include <ELEMYO.h>

#define   CSpin1         10
#define   CSpin2         9

#define   sensorInPin1   A0     // analog input pin that the 1st sensor is attached to
#define   sensorInPin2   A1     // analog input pin that the 2nd sensor is attached to

int signalReference = 524;      // reference of signal, 2.5 V for MYO, MYO-kit, BPM, BPM-kit
//int signalReference = 369;    // reference of signal, 1.8 V for MH-BPS101 and MH-BPS102

ELEMYO MyoSensor1(CSpin1);      // create ELEMYO object to work with signal
ELEMYO MyoSensor2(CSpin2);      // create ELEMYO object to work with signal

short tr1 = 100;        // trigger for 1st sensor
short tr2 = 100;        // trigger for 2nd sensor

void setup() {
  Serial.begin(115200);            // initialize serial communications at 115200 bps
  MyoSensor1.gain(x4);             // initial value of gain for 1st sensor
  MyoSensor2.gain(x8);             // initial value of gain for 2nd sensor
  pinMode(sensorInPin1, INPUT);    // initialize sensorInPin
  pinMode(sensorInPin2, INPUT);    // initialize sensorInPin
}

//-------------!!! Calibrate gain for each sensor before start !!!---------------------------------------------------------------------------
void loop() {
  //----reading and filtering signal of 1st sensor----
  int signalValue1 = analogRead(sensorInPin1);                 // read the analog in value:
  signalValue1 = MyoSensor1.BandStop(signalValue1, 50, 4);     // notch 50 Hz filter with band window 4 Hz.  
  signalValue1 = MyoSensor1.BandStop(signalValue1, 100, 6);    // notch 100 Hz (one of 50 Hz mode) filter with band window 6 Hz
  signalValue1 = MyoSensor1.movingAverage(signalValue1, signalReference,  0.96); // moving average transformation with 0.96 smoothing constant
  //--------------------------------------------

  //----reading and filtering signal of 2nd sensor----
  int signalValue2 = analogRead(sensorInPin2);                 // read the analog in value:
  signalValue2 = MyoSensor2.BandStop(signalValue2, 50, 4);     // notch 50 Hz filter with band window 4 Hz.  
  signalValue2 = MyoSensor2.BandStop(signalValue2, 100, 6);    // notch 100 Hz (one of 50 Hz mode) filter with band window 6 Hz
  signalValue2  = MyoSensor2.movingAverage(signalValue2, signalReference,  0.96); // moving average transformation with 0.96 smoothing constant
  //--------------------------------------------
  
  if (signalValue1 >= tr1 && signalValue2 < tr2)
    Serial.println(100);      // REPLACED by start command for your actuator START in direction 1

  if (signalValue1 < tr1 && signalValue2 >= tr2)
    Serial.println(-100);     // REPLACED by start command for your actuator  START in direction 2

  if ((signalValue1 < tr1 && signalValue2 < tr2) || (signalValue1 >= tr1 && signalValue2 >= tr2))
    Serial.println(0);        // REPLACED by start command for your actuator STOP
  
  delay(1);      // wait before the next loop
}

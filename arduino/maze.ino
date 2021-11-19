//This is where you define your library (tech libs)
#include <Wire.h>
#include "Adafruit_MPR121.h"

//Bit manipulation for Adafruit sensor
#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

//Define note frequencies
#define C_1 262
#define D_1 294
#define E_1 330
#define F_1 349
#define G_1 392
#define A_1 440
#define B_1 494
#define C_2 523
#define D_2 587
#define E_2 659
#define F_2 698
#define G_2 784

//Define ports name
const int buzzer = 9;
int LDR1 = A0;
int LDR2 = A1;
int LDR3 = A2;
int LDR4 = A3;
const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int LED4 = 5;

//Define variables
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;

/*
Maze Game
- Play the maze and then the ball will reach one of the 4 ending points
- When the ball reaches one of the ending points, LDR sensors will read the ball and light up the LED on the box
- When the LED lights up, put the hand into the box
- The hand will trigger the touch sensor
- Play the music depending on the box
*/

void setup()
{
    Serial.begin(9600);

    //keep Arduino board from starting too fast
    while(!Serial)
    {
        delay(10);
    }

    pinMode(buzzer, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

}

//Main Function
void loop()
{
    //LDR to check if ball has arrived at the point
    light_up();
    read_LDR();
}

//Control the LED
void light_up()
{
    Serial.println("LED control function");
    
    //Check first LDR sensor
    if (sensorValue1 < 35)
    {
        digitalWrite(LED1, HIGH);
    }
    else 
    {
        digitalWrite(LED1, LOW);
    }

    //Check second LDR sensor
    if (sensorValue2 < 35)
    {
        digitalWrite(LED2, HIGH);
    }
    else 
    {
        digitalWrite(LED2, LOW);
    }

    //Check 3rd LDR sensor
    if (sensorValue3 < 35)
    {
        digitalWrite(LED3, HIGH);
    }
    else 
    {
        digitalWrite(LED3, LOW);
    }

    //Check 4th LDR sensor
    if (sensorValue4 < 35)
    {
        digitalWrite(LED4, HIGH);
    }
    else 
    {
        digitalWrite(LED4, LOW);
    }

}

//Read the LDR reading (Analog)
void read_LDR()
{
    Serial.println("LDR reading function");
    
    sensorValue1 = analogRead(LDR1);
    sensorValue2 = analogRead(LDR2);
    sensorValue3 = analogRead(LDR3);
    sensorValue4 = analogRead(LDR4);

    //no obstacle is 100, lowest is 25
    Serial.println(sensorValue1);
    Serial.println(sensorValue2);
    Serial.println(sensorValue3);
    Serial.println(sensorValue4);

    delay(100);
    
}
//maze and ball, when the ball reaches the LDR sensor (4) -> LEDs lights up


//touch sensor 

//4 sensor, 4 lights, 4 songs

//


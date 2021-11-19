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
#define LDR1 = A0
#define LDR2 = A1
#define LDR3 = A2
#define LDR4 = A3
const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int LED4 = 5;


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
}

void read_LDR()
{
    Serial.println("LDR reading function");
    
}
//maze and ball, when the ball reaches the LDR sensor (4) -> LEDs lights up


//touch sensor 

//4 sensor, 4 lights, 4 songs

//


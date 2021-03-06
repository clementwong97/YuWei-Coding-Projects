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

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
uint16_t press = 0;

//Define the note frequencies (C1 D1 E1 F1 G1 A1 B1 C2 D2 E2 F2 G2)
int music_1[5] = {C_1, D_1, E_1, F_1, G_1};
int music_2[5] = {G_1, F_1, E_1, D_1, C_1};
int music_3[5] = {G_2, F_2, E_2, D_2, C_2};
int music_4[5] = {C_2, D_2, E_2, F_2, G_2};

// Change to 0.5 for a slower version of the song, 1.25 for a faster version
const float songSpeed = 1.0;


int durations[] = {
    125, 125, 250, 125, 125,
};

/*
Maze Game
- Play the maze and then the ball will reach one of the 4 ending points
- When the ball reaches one of the ending points, LDR sensors will read the ball and light up the LED on the box
- When the LED lights up, put the hand into the box
- The hand will trigger the touch sensor
- Play the music depending on the box
*/

//Setup Function
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

    Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
    // Default address is 0x5A, if tied to 3.3V its 0x5B
    // If tied to SDA its 0x5C and if SCL then 0x5D
    if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
    }
    Serial.println("MPR121 found!");
}

//Main Function
void loop()
{
    //LDR to check if ball has arrived at the point
    light_up();
    read_LDR();
    read_touch();
    play_music();
    
}

/********  Sub-Functions  *******/

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

//Enable Touch Sensor
void read_touch()
{
    // Get the currently touched pads
    currtouched = cap.touched();
  
    for (uint8_t i=0; i<5; i++) 
    {
        // it if *is* touched and *wasnt* touched before, alert!
        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) 
        {
            Serial.print(i); Serial.println(" touched");
            // for (uint8_t j=0; j<4; j++)
            // {
            //     tone(buzzer, note[j]);
            // }
            press = i;
        }

        // if it *was* touched and now *isnt*, alert!
        if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) 
        {
            Serial.print(i); Serial.println(" released");
            //noTone(buzzer);
        }
    }

    // reset our state
    lasttouched = currtouched;

    // // comment out this line for detailed data from the sensor!
    // return;

    // // debugging info, what
    // Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
    // Serial.print("Filt: ");
    // for (uint8_t i=0; i<12; i++) {
    //     Serial.print(cap.filteredData(i)); Serial.print("\t");
    // }
    // Serial.println();
    // Serial.print("Base: ");
    // for (uint8_t i=0; i<12; i++) {
    //     Serial.print(cap.baselineData(i)); Serial.print("\t");
    // }
    // Serial.println();
    
    // // put a delay so it isn't overwhelming
    // delay(100);
}

void play_music()
{
    if (press == 1)
    {
        for (uint8_t j=0; j<5; j++)
        {
            const int currentNote = music_1[j];
            float wait = durations[j] / songSpeed;
            // Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
            if (currentNote != 0)
            {
                tone(buzzer, music_1[j], wait);
            }
            else
            {
                noTone(buzzer);
                press = 0;
            }
            
            delay(wait);
        }

        press = 0;
    }
    else if (press == 2)
    {
        for (uint8_t j=0; j<5; j++)
        {
            const int currentNote = music_2[j];
            float wait = durations[j] / songSpeed;
            // Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
            if (currentNote != 0)
            {
                tone(buzzer, music_2[j], wait);
            }
            else
            {
                noTone(buzzer);
                press = 0;
            }
            
            delay(wait);
        }

        press = 0;
    }
    else if (press == 3)
    {
        for (uint8_t j=0; j<5; j++)
        {
            const int currentNote = music_3[j];
            float wait = durations[j] / songSpeed;
            // Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
            if (currentNote != 0)
            {
                tone(buzzer, music_3[j], wait);
            }
            else
            {
                noTone(buzzer);
                press = 0;
            }
            
            delay(wait);
        }

        press = 0;
    }
    else if (press == 4)
    {
        for (uint8_t j=0; j<5; j++)
        {
            const int currentNote = music_4[j];
            float wait = durations[j] / songSpeed;
            // Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
            if (currentNote != 0)
            {
                tone(buzzer, music_4[j], wait);
            }
            else
            {
                noTone(buzzer);
                press = 0;
            }
            
            delay(wait);
        }

        press = 0;
    }
}
//maze and ball, when the ball reaches the LDR sensor (4) -> LEDs lights up


//touch sensor 

//4 sensor, 4 lights, 4 songs

//


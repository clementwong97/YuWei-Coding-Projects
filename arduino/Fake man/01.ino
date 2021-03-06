//#include "pitches.h"

// Pin numbers
int speaker = 8;
int sensorIn1 = A1; // thumb - speed 
int sensorIn2 = A2; // pointer - meoldy
int sensorIn3 = A3; // middle - direction
int sensorIn4 = A4; // ring - random noteduration
//int sensorIn5 = A5; // pinky - daft punk 

int valSensorIn1 = 0;
int valSensorIn2 = 0;
int valSensorIn3 = 0;
int valSensorIn4 = 0;


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


int melody[] = {
NOTE_E4, NOTE_E4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G3,
NOTE_C4, NOTE_G3, NOTE_E3, NOTE_A3, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_E4, NOTE_G4, NOTE_A4,
};

int melody2[] = {
NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_B3,
NOTE_C4, NOTE_G3, NOTE_E3, NOTE_A3, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_B3,
};

int melody3[] = {
NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_GS3, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_C5, NOTE_C5, NOTE_C5,
NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_GS3, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_C4,
};

int melody4[] = {
NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A3, NOTE_G3, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A3, NOTE_G3
};


// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
8,4,4,8,4,2,2,
3,3,3,4,4,8,4,8,8,8,4,8,4,3,8,8,3,
3,3,3,4,4,8,4,8,8,8,4,8,4,3,8,8,2,
8,8,8,4,4,8,8,4,8,8,3,8,8,8,4,4,4,8,2,
8,8,8,4,4,8,8,4,8,8,3,3,3,1,
8,4,4,8,4,8,4,8,2,8,4,4,8,4,1,
8,4,4,8,4,8,4,8,2
};

//Define the note frequencies (C1 D1 E1 F1 G1 A1 B1 C2 D2 E2 F2 G2)
int note[12] = {262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784};

int note2[9] = {330, 294, 262, 330, 294, 262, 330, 294, 262};

int note3[10] = {494, 523,494, 523,494, 523,494, 523,494, 523};

//int note4[10] = {698,698,494,698};
int note4[10] = { NOTE_E4, NOTE_C4, NOTE_A3, NOTE_G3};
  

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

pinMode(speaker, OUTPUT);

pinMode(sensorIn1,INPUT);
pinMode(sensorIn2,INPUT);
pinMode(sensorIn3,INPUT);
pinMode(sensorIn4,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  valSensorIn1 = analogRead(sensorIn1);
  valSensorIn2 = analogRead(sensorIn2);
  valSensorIn3 = analogRead(sensorIn3);
  valSensorIn4 = analogRead(sensorIn4);


//A0 "right leg"
for(int b=0; b<12; b++){
    if( valSensorIn1 > 679 && valSensorIn1 < 682){ 
    tone(speaker,melody[b]);
    }else{
    tone(speaker,note[b]);
  }
   delay(100);
  }


//A1 "left hand"
  for(int b=0; b<20; b++){
    if( valSensorIn2 > 679 && valSensorIn2 < 682){ 
    tone(speaker,melody2[b]);
    }else{
    tone(speaker,note2[b]);
  }
   delay(100);
  }

//A2 "left leg"
for(int b=0; b<9; b++){
    if( valSensorIn3 > 676 && valSensorIn3 < 680){ 
    tone(speaker,melody3[b]);
    }else{
    tone(speaker,note2[b]);
  }
   delay(100);
  }
  

//A3 "right hand"
for(int b=0; b<10; b++){
    if( valSensorIn4 < 550){ 
    tone(speaker,melody4[b]);
    }else if( valSensorIn4 > 550 && valSensorIn4 < 600){
    tone(speaker,note3[3+b]);
  }else if( valSensorIn4 > 600){
    tone(speaker,note4[3+b]);
  }
   delay(100);
  }
  

//  Serial.println("right leg");
//  Serial.println(valSensorIn1);
//  Serial.println("left hand");
//  Serial.println(valSensorIn2);
//  Serial.println("left leg");
//  Serial.println(valSensorIn3);
  Serial.println("right hand");
  Serial.println(valSensorIn4);

  

}
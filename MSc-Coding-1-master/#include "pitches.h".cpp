#include "pitches.h"

// Pin numbers
int speakerOutputPin = 8;
int sensorIn1 = A0; // thumb - speed 
int sensorIn2 = A1; // pointer - meoldy
int sensorIn3 = A2; // middle - direction
int sensorIn4 = A3; // ring - random noteduration
int sensorIn5 = A4; // pinky - daft punk 
// Daft Punk melody and corresponding note durations
int daftPunkMelody[] = {
  NOTE_G4, NOTE_F4, NOTE_G4, NOTE_AS4, NOTE_D4, 
  NOTE_D4, NOTE_C4, NOTE_D4, NOTE_F4, NOTE_AS3, 
  NOTE_AS3, NOTE_A3, NOTE_AS3, NOTE_D4, NOTE_G3, 
  NOTE_G3, NOTE_A3, NOTE_AS3 
};
// note durations: 2 = half note, 4 = quarter note, 8 = eighth note, etc.:
int daftPunkNoteTypes[] = {
  2, 8, 8, 8, 8, 
  2, 8, 8, 8, 8, 
  2, 8, 8, 8, 8, 
  2, 4, 4
};
// Arpegio melodies controled by pointer finger
int melodyA[] = {
   NOTE_G3, NOTE_B3, NOTE_D4, NOTE_E4
};
int melodyB[] = {
   NOTE_A3, NOTE_C4, NOTE_E4, NOTE_G4
};
int melodyC[] = {
   NOTE_E3, NOTE_G3, NOTE_B3, NOTE_D4
};
int melodyD[] = {
  NOTE_C3, NOTE_E3, NOTE_G3, NOTE_B3
};
// initial starting values for inputs before calibration
int initialSensorValue1 = 800;
int initialSensorValue2 = 1000;
int initialSensorValue3 = 1000;
int initialSensorValue4 = 1000;
int initialSensorValue5 = 1000;
// resistance point ranges for five inputs
int sensorRange1 = 250; // thumb
int sensorRange2 = 500; // pointer
int sensorRange3 = 500; // middle
int sensorRange4 = 500; // ring
int sensorRange5 = 700; // pinky
// whether we should play arpegio melody forward or backward
bool isForward = true;
// when adding random not interference (ring finger), perctange of notes that should be modified
int randomNoteTypePercent = 20;
// whether we should play daft punk melody or not
bool shouldPlayDaftPunk = false;
void setup() {
  Serial.begin(9600); //start printing out to the serial port for processing to read from
  // initialize the input pins
  pinMode(sensorIn1, INPUT);//add a input for your potentiometer  
  pinMode(sensorIn2, INPUT);//add a input for your potentiometer  
  pinMode(sensorIn3, INPUT);//add a input for your potentiometer 
  pinMode(sensorIn4, INPUT);//add a input for your potentiometer  
  pinMode(sensorIn5, INPUT);//add a input for your potentiometer  
 
  // calibrate the initial values for the pins
  getInitialSensorValues();
}
// Callibrates the initial sensor values for the five inputs
void getInitialSensorValues() {
   initialSensorValue1 = analogRead(sensorIn1); //take an analog read on the knob to read resistance(0 to 1024)
   initialSensorValue2 = analogRead(sensorIn2); //take an analog read on the knob to read resistance(0 to 1024)
   initialSensorValue3 = analogRead(sensorIn3); //take an analog read on the knob to read resistance(0 to 1024)
   initialSensorValue4 = analogRead(sensorIn4); //take an analog read on the knob to read resistance(0 to 1024)
   initialSensorValue5 = analogRead(sensorIn5); //take an analog read on the knob to read resistance(0 to 1024)
}
// Gets the note duration to play given mapped sensor inputs from thumb and ring finger
int getNoteDuration(int dataMapped, int dataMapped4) {
  int noteType = 4; // quarter; 
   if (dataMapped4 > 75) {
     if (random(0, 100) <= randomNoteTypePercent) {
        noteType = 8; // eight
     }
   }
   int noteDuration = dataMapped / noteType;
   return noteDuration;
}
// Plays daft punk melody through to completion
void playDaftPunk() {
  for (int thisNote = 0; thisNote < 18; thisNote++) {     
      int note = daftPunkMelody[thisNote];
      int noteType = daftPunkNoteTypes[thisNote];  
      int noteDuration = 1000 / daftPunkNoteTypes[thisNote];
      
      tone(speakerOutputPin, note, noteDuration);
     
      int pauseBetweenNotes = noteDuration * 1.3;
      delay(pauseBetweenNotes);
      noTone(speakerOutputPin);
    }
}
void loop() {
   // get, map, and print sensor inputs
   int inputData = analogRead(sensorIn1); //take an analog read on the knob to read resistance(0 to 1024)
   int inputData2 = analogRead(sensorIn2); //take an analog read on the knob to read resistance(0 to 1024)
   int inputData3 = analogRead(sensorIn3); //take an analog read on the knob to read resistance(0 to 1024)
   int inputData4 = analogRead(sensorIn4); //take an analog read on the knob to read resistance(0 to 1024)
   int inputData5 = analogRead(sensorIn5); //take an analog read on the knob to read resistance(0 to 1024)
  
   int dataMapped = map(inputData, initialSensorValue1 - sensorRange1, initialSensorValue1, 250, 1000);//using the map function, transform the range of the 
   dataMapped = constrain(dataMapped, 250, 1000);
    
   int dataMapped2 = map(inputData2, initialSensorValue2, initialSensorValue2 - sensorRange2, 0, 100);//using the map function, transform the range of the 
   dataMapped2 = constrain(dataMapped2, 0, 100);
   int dataMapped3 = map(inputData3, initialSensorValue3, initialSensorValue3 - sensorRange3, 0, 100);//using the map function, transform the range of the 
   dataMapped3 = constrain(dataMapped3, 0, 100);
   int dataMapped4 = map(inputData4, initialSensorValue4, initialSensorValue4 - sensorRange4, 0, 100);//using the map function, transform the range of the 
   dataMapped4 = constrain(dataMapped4, 0, 100);
   int dataMapped5 = map(inputData5, initialSensorValue5, initialSensorValue5 - sensorRange5, 0, 100);//using the map function, transform the range of the 
   dataMapped5 = constrain(dataMapped5, 0, 100);
   Serial.println("----------------");
   Serial.print("inputData1: ");
   Serial.print(inputData);
   Serial.print("; mapped: ");
   Serial.println(dataMapped);
   Serial.print("inputData2: ");
   Serial.print(inputData2);
   Serial.print("; mapped: ");
   Serial.println(dataMapped2);
   Serial.print("inputData3: ");
   Serial.print(inputData3);
   Serial.print("; mapped: ");
   Serial.println(dataMapped3);
   Serial.print("inputData4: ");
   Serial.print(inputData4);
   Serial.print("; mapped: ");
   Serial.println(dataMapped4);
   Serial.print("inputData5: ");
   Serial.print(inputData5);
   Serial.print("; mapped: ");
   Serial.println(dataMapped5);
  // check which direction to play the arpegio melody
  if (dataMapped3 < 50) {
    isForward = true;
  } else {
    isForward = false;
  }
  // determine if we should play daft punk melody
  if (dataMapped > 800 && dataMapped2 < 40 && dataMapped3 > 60 && dataMapped4 > 60 && dataMapped5 < 40) {
    shouldPlayDaftPunk = true;
  } else {
    shouldPlayDaftPunk = false;
  }
   if (shouldPlayDaftPunk) {
    // play daft punk melody
    playDaftPunk();
   } else {
     // play arpegio forward
     if (isForward) {
        for (int thisNote = 0; thisNote < 4; thisNote++) {     
          // get note duration
          int noteDuration = getNoteDuration(dataMapped, dataMapped4);    
          // determine which melody to play
          if (dataMapped2 < 25) {
            tone(speakerOutputPin, melodyA[thisNote], noteDuration);
          } else if (dataMapped2 > 25 && dataMapped2 <= 50) {
           tone(speakerOutputPin, melodyB[thisNote], noteDuration);
          } else if (dataMapped2 > 50 && dataMapped2 <= 75) {
            tone(speakerOutputPin, melodyC[thisNote], noteDuration);
          } else {
            tone(speakerOutputPin, melodyD[thisNote], noteDuration);
          }
          
          int pauseBetweenNotes = noteDuration * 1.3;
          delay(pauseBetweenNotes);
          noTone(speakerOutputPin);
        }
     } else {
      // // play arpegio backward
      for (int thisNote = 3; thisNote >= 0; thisNote--) {
          // get note duration
          int noteDuration = getNoteDuration(dataMapped, dataMapped4);   
          // determine which melody to play
          if (dataMapped2 < 25) {
            tone(speakerOutputPin, melodyA[thisNote], noteDuration);
          } else if (dataMapped2 > 25 && dataMapped2 <= 50) {
           tone(speakerOutputPin, melodyB[thisNote], noteDuration);
          } else if (dataMapped2 > 50 && dataMapped2 <= 75) {
            tone(speakerOutputPin, melodyC[thisNote], noteDuration);
          } else {
            tone(speakerOutputPin, melodyD[thisNote], noteDuration);
          }
          
          int pauseBetweenNotes = noteDuration * 1.3;
          delay(pauseBetweenNotes);
          noTone(speakerOutputPin);
        }
     }
   }
  // delay(200);
}
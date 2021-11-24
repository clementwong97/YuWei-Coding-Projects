//Define port name
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

//Setup Function
void setup()
{
    Serial.begin(9600);

    //keep Arduino board from starting too fast
    while(!Serial)
    {
        delay(10);
    }

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
    Serial.println("LDR 1");
    Serial.println(sensorValue1);
    Serial.println("LDR 2");
    Serial.println(sensorValue2);
    Serial.println("LDR 3");
    Serial.println(sensorValue3);
    Serial.println("LDR 4");
    Serial.println(sensorValue4);

    delay(100);
    
}
#include <Wire.h>

#define SLAVE_ADDRESS 0x60
#define photocell1  0
#define photocell2  1
#define frontLights  2
#define leftLights  3
#define rightLights  4
#define trigBack 5
#define echoBack 6
#define hallSensor 7
#define trigLeft 8
#define echoLeft 9
#define trigRight 10
#define echoRight 11
#define trigFront 12
#define echoFront 13

int lightIntensity1, lightIntensity2;
float  distance;
long durationFront, distanceFront, durationBack, distanceBack, durationRight, distanceRight, durationLeft, distanceLeft;
int numRotations = 0;
bool hallSensorPosition = 0, comand;
String df, db, dl, dr, dist;
 
void setup()
{
  Wire.begin(); 
  randomSeed(analogRead(3));
  Serial.begin(9600);  
  pinMode(frontLights, OUTPUT);
  pinMode(leftLights, OUTPUT);
  pinMode(rightLights, OUTPUT);
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
  pinMode(trigBack, OUTPUT);
  pinMode(echoBack, INPUT);
  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);
  pinMode(hallSensor, INPUT);
}

byte x = 0;

void loop()
{
  //Comenzile pentru placa de jos
  
  while (Serial.available())
  {
  x = Serial.read();
  Serial.println (x);
  if (x<=120 && x>=60)
  {
    Serial.println("DIRECTIE");
    if (x <=95 && x>=85)
      {
        digitalWrite (leftLights, LOW);
        digitalWrite (rightLights, LOW);
      }
     else if (x<85)
      {
        digitalWrite (leftLights, HIGH);
        digitalWrite (rightLights, LOW);
      }
     else
     {
        digitalWrite(rightLights,HIGH);
        digitalWrite(leftLights, LOW);
     }
  }
  else if (x>150 && x<250)
    {
      distance = ((x-150)*10)/16;
      Serial.println ("DISTANTA");
    }
  else Serial.println ("VITEZA");
  if (distance <= numRotations)
  {
    x = 0;
    numRotations = 0;
  }
  // Transmision to slave
  
  Wire.beginTransmission(0x60);   
  Wire.write(x);                
  Wire.endTransmission();      
  Wire.requestFrom(SLAVE_ADDRESS, 1);
  int bytes = Wire.available();
  for(int i = 0; i< bytes; i++)
    x = Wire.read();

  } 
/*
  //Luminile
  
  lightIntensity1 = analogRead(photocell1);
  lightIntensity2 = analogRead(photocell2);
  if (lightIntensity1 < 500 || lightIntensity2 <500) 
      digitalWrite(frontLights, HIGH);
  else digitalWrite (frontLights,LOW);

 //partea de senzor hall*/

  int hall = digitalRead(hallSensor);
  if ((hall == 0 && hallSensorPosition == 1) || (hall == 1 && hallSensorPosition == 0))
    {
        numRotations++;
     Serial.write(numRotations);
    }
  hallSensorPosition = hall;
  
  //Distantele
  /*
 
  digitalWrite(trigFront, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigFront, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigFront, LOW); 
  durationFront = pulseIn(echoFront, HIGH);
  distanceFront = (durationFront/2) / 29.1;
  if (distanceFront <= 20 && forward)
  Serial.write(250);
 // Serial.println(distanceFront); 
    
  digitalWrite(trigBack, LOW);
  delayMicroseconds(2);
  digitalWrite(trigBack, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigBack, LOW);
  durationBack = pulseIn(echoBack, HIGH);
  distanceBack = (durationBack/2) / 29.1;
  if (distanceBack <= 20 && !forward)
    Serial.write(251);
   // Serial.println(distanceBack); 
  
  digitalWrite(trigLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigLeft, LOW);
  durationLeft = pulseIn(echoLeft, HIGH);
  distanceLeft = (durationLeft/2) / 29.1;
 // if (distanceLeft <= 15)
   // Serial.write (252);
   // Serial.println (distanceLeft);
    
  digitalWrite(trigRight, LOW);
  delayMicroseconds(2);
  digitalWrite(trigRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigRight, LOW);
  durationRight = pulseIn(echoRight, HIGH);
  distanceRight = (durationRight/2) / 29.1;
//  if (distanceRight <= 15)
//    Serial.write(253); */

}



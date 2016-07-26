#include <Servo.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x60
byte x = 0x00;
int last = 0;
int enableMotor = 3;
int motor1 = 4;
int motor2 = 7;
Servo directionServo, front, left, back, right;
void setup()
{
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
  pinMode (enableMotor, OUTPUT);
  pinMode (motor1, OUTPUT);
  pinMode (motor2, OUTPUT);
  directionServo.attach(5);
  front.attach(6);
  left.attach(9);
  back.attach(10);
  right.attach(11);
}

void loop()
{
  delay(100);
}

void requestEvent() 
{
  Wire.write(x);
}

void receiveEvent(int bytes)
{
  if(Wire.available() != 0)
  {
    for(int i = 0; i< bytes; i++)
    {
      x = Wire.read();
      Serial.println (x);
      if (x>=0 && x<=25)
        forward(x*10);
      else if (x>=30 && x<=55)
        backward((x-30)*10);
      else if (x>=60 && x<=120)
        directionServo.write(x);
      else if (last == 125)
        front.write((x-100)*2);
      else if (last == 130)
        left.write((x-100)*2);
      else if (last == 135)
        back.write((x-100)*2);
      else if (last == 140)
        right.write((x-100)*2);
      last = x;
    }
  }
}

void forward (int speed1)
{
 analogWrite (enableMotor, speed1);
 digitalWrite (motor1, LOW);
 digitalWrite (motor2, HIGH);
}

void backward (int speed1)
{
 digitalWrite (enableMotor, speed1);
 digitalWrite (motor1, HIGH);
 digitalWrite (motor2, LOW);
}

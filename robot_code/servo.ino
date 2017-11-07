#include <Servo.h>

#define servoPin 10

Servo servo;

void initServo()
{
  pinMode(servoPin, OUTPUT);
  servo.attach(servoPin);
}

void turnServo(int i)
{
  if(i >= 0 && i <= 180)
  {
    servo.write(i);
  }
}


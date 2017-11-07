void setup()
{
  //initialization
  Serial.begin(9600);
  initSensors();
  initServo();
  turnServo(180);
  initMotors();

  //move and stuff
  //forward();
  //setR(1.0);
  //setL(-1.0);
  //delay(5000);
  //halt();
}

void loop()
{
  delay(500);
  printAllSensors();
}

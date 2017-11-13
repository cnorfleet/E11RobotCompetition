void setup()
{
  //initialization
  Serial.begin(9600);
  initSensors();
}

void loop()
{
  delay(500);
  printAllSensors();
}

#define distSensor 14
#define photoSensor 19
#define irReflectSensor 18

void initSensors()
{
  pinMode(distSensor, INPUT);
  pinMode(photoSensor, INPUT);
  pinMode(irReflectSensor, INPUT);
}

void printAllSensors()
{
  Serial.print("Distance Sensor: ");
  Serial.print(analogRead(distSensor - 14));
  Serial.print(", Phototransistor Sensor: ");
  Serial.print(analogRead(photoSensor - 14));
  Serial.print(", and IR Reflectance Sensor: ");
  Serial.println(analogRead(irReflectSensor - 14));
}


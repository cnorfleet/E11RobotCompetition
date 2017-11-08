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
  Serial.print("Dist Sensor: ");
  Serial.print(readDist());
  Serial.print(", Photo Sensor: ");
  Serial.print(readPhoto());
  Serial.print(", IR Reflect Sensor: ");
  Serial.println(readIrReflect());
}

int readIrReflect()
{ return analogRead(irReflectSensor - 14); }

int readPhoto()
{ return analogRead(photoSensor - 14); }

int readDist()
{ analogRead(distSensor - 14); }

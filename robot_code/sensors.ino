#define distSensor 14
#define photoSensor 19
#define irReflectSensor 18
#define irReflectSensor2 17

void initSensors()
{
  pinMode(distSensor, INPUT);
  pinMode(photoSensor, INPUT);
  pinMode(irReflectSensor, INPUT);
  pinMode(irReflectSensor2, INPUT);
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

int readIrReflect2()
{ return analogRead(irReflectSensor2 - 14); }

int readPhoto()
{ return analogRead(photoSensor - 14); }

int readDist()
{ analogRead(distSensor - 14); }

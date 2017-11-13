#define photoSensor 14
#define irReflectSensor1 15
#define irReflectSensor2 16
#define irReflectSensor3 17
#define irReflectSensor4 18
#define irReflectSensor5 19

int irSensorPins[5] = { irReflectSensor1, irReflectSensor2, irReflectSensor3, irReflectSensor4, irReflectSensor5 };

void initSensors()
{
  pinMode(photoSensor, INPUT);
  pinMode(irReflectSensor1, INPUT);
  pinMode(irReflectSensor2, INPUT);
  pinMode(irReflectSensor3, INPUT);
  pinMode(irReflectSensor4, INPUT);
  pinMode(irReflectSensor5, INPUT);
}

void printAllSensors()
{
  Serial.print("Phototransistor Sensor: ");
  Serial.print(readPhoto());
  Serial.print(" and IR Reflectance Sensors: ");
  for(int i = 0; i < 5; i++)
  { Serial.print(readIr(i+1)); if(i != 4) { Serial.print(", "); } }
  Serial.println();
}

int readSensor(int pin)
{ return analogRead(pin - 14); }

int readPhoto()
{ return readSensor(photoSensor); }

int readIr(int num)
{ return readSensor(irSensorPins[num-1]); }

int readIrAvg()
{
  int total = 0;
  for (int i = 0; i < 5; i++)
  { total += readIr(i+1); }
  return total/5;
}


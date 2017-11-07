#define LPlus 9
#define LMinus 8
#define RPlus 7
#define RMinus 12
#define LEN 6
#define REN 11

int powerLevel = 255;

void initMotors()
{
  pinMode(LPlus, OUTPUT);
  pinMode(LMinus, OUTPUT);
  pinMode(RPlus, OUTPUT);
  pinMode(RMinus, OUTPUT);
  pinMode(REN, OUTPUT);
  pinMode(LEN, OUTPUT);
  digitalWrite(LEN, HIGH);
  digitalWrite(REN, HIGH);
  //halt();
}

void setPowerLevel(int pwr)
{
  powerLevel = pwr;
}

void halt()
{
  analogWrite(RPlus, 0);
  analogWrite(RMinus, 0);
  analogWrite(LPlus, 0);
  analogWrite(LMinus, 0);
}

void forward()
{
  analogWrite(RPlus, powerLevel);
  analogWrite(RMinus, 0);
  analogWrite(LPlus, powerLevel);
  analogWrite(LMinus, 0);
}

void forward(int t)
{
  forward();
  delay(t);
  halt();
}

void backward()
{
  analogWrite(RPlus, 0);
  analogWrite(RMinus, powerLevel);
  analogWrite(LPlus, 0);
  analogWrite(LMinus, powerLevel);
}

void backward(int t)
{
  backward();
  delay(t);
  halt();
}

void turnR()
{
  analogWrite(RPlus, 0);
  analogWrite(RMinus, powerLevel);
  analogWrite(LPlus, HIGH);
  analogWrite(LMinus, 0);
}

void turnR(int t)
{
  turnR();
  delay(t);
  halt();
}

void turnL()
{
  analogWrite(RPlus, powerLevel);
  analogWrite(RMinus, 0);
  analogWrite(LPlus, 0);
  analogWrite(LMinus, powerLevel);
}

void turnL(int t)
{
  turnL();
  delay(t);
  halt();
}

//accepts double from -1 to 1
void setR(double i)
{
  boolean dir = (i >= 0);
  int i2 = (int) (abs(i) * 255.0);
  Serial.println(i2);
  Serial.println(dir);
  if(dir)
  {
    Serial.print("dafdjsahfd");
    analogWrite(RPlus, i2);
    analogWrite(RMinus, 0);
  }
  else
  {
    analogWrite(RPlus, 0);
    analogWrite(RMinus, i2);
  }
}

//accepts double from -1 to 1
void setL(double i)
{
  boolean dir = (i >= 0);
  int i2 = (int) (abs(i) * 255.0);
  Serial.println(i2);
  Serial.println(dir);
  if(dir)
  {
    Serial.print("dafdjsahfd");
    analogWrite(LPlus, i2);
    analogWrite(LMinus, 0);
  }
  else
  {
    analogWrite(LPlus, 0);
    analogWrite(LMinus, i2);
  }
}

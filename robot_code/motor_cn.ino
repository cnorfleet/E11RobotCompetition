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
  halt();
}

void halt()
{
  analogWrite(RPlus, 0);
  analogWrite(RMinus, 0);
  analogWrite(LPlus, 0);
  analogWrite(LMinus, 0);
}

void setR(int i)
{
  if(i>=0)
  {
    analogWrite(RMinus, min(i,255));
    analogWrite(RPlus, 0);
  }
  else
  {
    analogWrite(RMinus, 0);
    analogWrite(RPlus, max(-i,-255));
  }
}

void setL(int i)
{
  if(i >= 0)
  {
    analogWrite(LMinus, min(i,255));
    analogWrite(LPlus, 0);
  }
  else
  {
    analogWrite(LMinus, 0);
    analogWrite(LPlus, max(-i,-255));
  }
}

//general function things:
void setPowerLevel(int pwr)
{ powerLevel = pwr; }

void forward()
{
  analogWrite(RPlus, powerLevel);
  analogWrite(RMinus, 0);
  analogWrite(LPlus, powerLevel);
  analogWrite(LMinus, 0);
}

void backward()
{
  analogWrite(RPlus, 0);
  analogWrite(RMinus, powerLevel);
  analogWrite(LPlus, 0);
  analogWrite(LMinus, powerLevel);
}

void turnR()
{
  analogWrite(RPlus, 0);
  analogWrite(RMinus, powerLevel);
  analogWrite(LPlus, HIGH);
  analogWrite(LMinus, 0);
}

void turnL()
{
  analogWrite(RPlus, powerLevel);
  analogWrite(RMinus, 0);
  analogWrite(LPlus, 0);
  analogWrite(LMinus, powerLevel);
}

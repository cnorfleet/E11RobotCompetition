#define LPlus 9
#define LMinus 8
#define RPlus 7
#define RMinus 12
#define LEN 6
#define REN 11

int powerLevel = 150;

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
    analogWrite(RPlus, min(i,255));
    analogWrite(RMinus, 0);
  }
  else
  {
    analogWrite(RPlus, 0);
    analogWrite(RMinus, max(-i,-255));
  }
}

void setL(int i)
{
  if(i >= 0)
  {
    analogWrite(LPlus, min(i,255));
    analogWrite(LMinus, 0);
  }
  else
  {
    analogWrite(LPlus, 0);
    analogWrite(LMinus, max(-i,-255));
  }
}

//general function things:
void setPowerLevel(int pwr)
{
  if(powerLevel > 255) { powerLevel = 255; }
  else if (powerLevel < -255) { powerLevel = -255; }
  else { powerLevel = pwr; }
}

void forward()
{
  setR(powerLevel);
  setL(powerLevel);
}

void backward()
{
  setR(-powerLevel);
  setL(-powerLevel);
}

void turnR()
{
  setR(-powerLevel);
  setL(powerLevel);
}

void turnL()
{
  setR(powerLevel);
  setL(-powerLevel);
}


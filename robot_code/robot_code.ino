/**
 * robot code for the E11 competition
 * Caleb, Howard, and Lorelei
 * November 2017
 */

#define LEDpin 13
#define teamPin 3
boolean whiteTeam;

#define gcLength 31
#define numRegisters 5
#define numGoldCodes 8
boolean GC[9][31] = {{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1},
                      {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0},
                      {0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
                      {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1},
                      {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1},
                      {1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
                      {0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0},
                      {1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1},
                      {0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}};

//IR reflectance thresholds
#define startBoxThreshold 700
#define lineThreshold 790
#define circleThreshold 940

//line following speeds
#define outSpeed 0.8
#define outSpeed2 -0.2
#define inSpeed 1
#define inSpeed2 0.5

void setup()
{
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
  pinMode(teamPin, INPUT);
  digitalWrite(LEDpin, LOW);
  delay(200);
  whiteTeam = (digitalRead(teamPin) == LOW);

  //get to far beacon #3://
  while(readIrReflect() < lineThreshold)
  { forward(); delay(5); }

  //turn a bit
  setR(125);
  setL(80);
  delay(500);
  halt();

  //follow line
  while(readBeacon != -3)
  {
    int r = readIrReflect();
    if(r < lineThreshold); //turn left
    { 
      setR
    }
    else //turn right
    {
      
    }
  }
}

void loop()
{
  /*
  Serial.println(readCode());
  flashCode(5);
  delay(10);
  flashCode(6);
  delay(10);
  flashCode(7);
  delay(10);
  flashCode(8);
  delay(10);
  flashCode(9);
  delay(10);
  */
}



void flashCode(int beaconNum)
{
  unsigned long startReadTime = micros();
  int interval = 250;
  for(int i = 0; i < gcLength;)
  {
    if(micros() > startReadTime + (interval * i))
    {
      if(XOR(GC[abs(beaconNum - 1)][i], whiteTeam)) { digitalWrite(LEDpin, HIGH); }
      else { digitalWrite(LEDpin, LOW); }
      i++;
    }
  }
}

boolean XOR(boolean a, boolean b)
{ return((a && !b) || (!a && b)); }

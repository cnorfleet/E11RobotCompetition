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

void setup()
{
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
  pinMode(teamPin, INPUT);
  digitalWrite(LEDpin, LOW);
  delay(200);
  whiteTeam = (digitalRead(teamPin) == LOW);
}

void loop()
{
  Serial.println(readCode());
  flashCode(4);
  delay(10);
  flashCode(5);
  delay(10);
  flashCode(6);
  delay(10);
  flashCode(7);
  delay(10);
  flashCode(8);
  delay(10);
}

void flashCode(int codeIdx)
{
  
  unsigned long startReadTime = micros();
  int interval = 250;
  for(int i = 0; i < gcLength;)
  {
    if(micros() > startReadTime + (interval * i))
    {
      if(XOR(GC[abs(codeIdx)][i], whiteTeam)) { digitalWrite(LEDpin, HIGH); }
      else { digitalWrite(LEDpin, LOW); }
      i++;
    }
  }
}

boolean XOR(boolean a, boolean b)
{
  return((a && !b) || (!a && b));
}


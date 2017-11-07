/**
 * robot code for the E11 competition
 * Caleb, Howard, and Lorelei
 * November 2017
 */

#define LEDpin 13

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
  delay(200);
}

void loop()
{
  // put your main code here, to run repeatedly:
}

void flashCode(int codeNum)
{
  unsigned long startReadTime = micros();
  int interval = 250;
  for(int i = 0; i < gcLength;)
  {
    if(micros() > startReadTime + (interval * i))
    {
      if(GC[codeNum][i]) { digitalWrite(LEDpin, HIGH); }
      else { digitalWrite(LEDpin, LOW); }
      i++;
    }
  }
}

#define threshold
int readCode()
{
  //read light values
  unsigned long startReadTime = micros();
  int lightVals[gcLength] = {};
  int avgVal = 0;
  #define interval 250
  for(int i = 0; i < gcLength;)
  {
    //Serial.println(micros() - startReadTime);
    if(micros() > startReadTime + (interval * i))
    {
      int photo = readPhoto();
      lightVals[i] = photo;
      avgVal += photo;
      i++;
    }
  }
  //convert read values to binary gold code
  boolean code[gcLength] = {};
  avgVal = avgVal / gcLength;
  for(int i = 0; i < 31; i++)
  {
    if(lightVals[i] > avgVal)
    { code[i] = 0; }
    else
    { code[i] = 1; }
  }
  
  //correlation
  int thisIs = whichCode(code);
  /*Serial.print("ID # = "); Serial.println(abs(thisIs) / 100);
  Serial.print("Corresponding correlation = "); Serial.println(thisIs % 100);
  Serial.print("Team color = ");
  if(thisIs > 0) { Serial.println("White"); } else { Serial.println("Green"); } //*/

  int beaconNum = abs(thisIs)/100;
  //Serial.println(thisIs);
  if(beaconNum >= 5 and abs(thisIs)%100 > 29)
  { setR(255); setL(-255); delay(250); }
  else { setR(0); setL(0); }
}


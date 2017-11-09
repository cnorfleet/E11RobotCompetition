#define thresholdCor 23
#define LEDpin 13

#define gcLength 31
#define numRegisters 5
#define numGoldCodes 8
#define intervalFlash 250 //micro sec
boolean GC[9][31] = {{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1},
                      {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0},
                      {0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
                      {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1},
                      {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1},
                      {1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
                      {0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0},
                      {1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1},
                      {0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}};

///////////// reading gc from beacon ////////////////

int readBeacon()
{
  int thisIs = readCode();
  int beaconNum = thisIs/100; //abs(thisIs)/100
  return beaconNum;
}

int readBeaconWell()
{
  int c = readCode();
  int beaconNum = c/100;
  if ((abs(c) % 100) < 20) { return 0; }
  if(readBeacon() != beaconNum) { return 0; }
  if(readBeacon() != beaconNum) { return 0; }
  return beaconNum;
}

int readCode()
{
  //read light values
  unsigned long startReadTime = micros();
  int lightVals[gcLength] = {};
  int avgVal = 0;
  for(int i = 0; i < gcLength;)
  {
    //Serial.println(micros() - startReadTime);
    if(micros() > startReadTime + (intervalFlash * i))
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
  return thisIs;
}

//for weird reasons I decided to make this return 100 * the number of the code (indexed from 1) + the absolute value of the correlation
//also, the returned value is negative for "inverse" correlation (i.e. green team) and positive for white team
int whichCode(boolean code[gcLength])
{
  int maxCorrelation = 0;
  int bestFitCode = 0;
  for(int i = 0; i < numGoldCodes; i++)
  {
    int corr = getCorrelation(code, GC[i]);
    if(abs(corr) > abs(maxCorrelation))
    { maxCorrelation = corr; bestFitCode = i; }
  }
  //return (bestFitCode + 1) * maxCorrelation / abs(maxCorrelation);
  return (((bestFitCode + 1)*100) +  abs(maxCorrelation)) * (maxCorrelation / abs(maxCorrelation));
}

int getCorrelation(boolean code1[gcLength], boolean code2[gcLength])
{
  int max = 0;
  //find correlation at each offset
  for(int k = 0; k < gcLength; k++)
  {
    int temp = getDotProduct(code1, code2, k);
    //Serial.print(String(temp) + " ");
    if(abs(temp) > abs(max)) { max = temp; }
  }
  return max;
}

int getDotProduct(boolean code1[gcLength], boolean code2[gcLength], int offset2)
{
  int total = 0;
  for(int i = 0; i < gcLength; i++)
  {
    int loc = i + offset2;
    if(loc >= gcLength) { loc -= gcLength; }
    total += dot(code1[i], code2[loc]);
  }
  return total;
}

int dot(int i, int j)
{
  if(i == j) { return 1; }
  else { return -1; }
}

/////////// flashing gc to beacon //////////////////

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

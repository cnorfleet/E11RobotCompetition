/**
 * State for following blue line
 * Behaviors:
 * if see unclaimed bump beacon, slow down and go forward along blue line**
 * if see claimed bump beacon and time is almost up, go to go home state **
 * else if see claimed bump beacon, turn around**
 * if can't find blue line anymore, return to main state
 */
 double blueMoveSpeed = 120.0;
 unsigned long lastTime;
 int t;
void followBlueLine()
{
  t = 0;
  lastTime = millis();
  double blueLoc = getBlueLineLoc();
  while(blueLoc != -1)
  { t++;
    int bNum = readBeaconWell();
    if(isCornerBeacon(bNum) and not (XOR(bNum < 0, whiteTeam)))
    {  //if see claimed bump beacon:
      if(false) //if time is almost up, go home
      { headHome(bNum % 2 == 0); }
      else //otherwise, turn around
      {
        setR(-255); setL(-255);
        delay(250);
        setR(255); setL(-255);
        delay(200);
      }
    }
    else if (t > 50)
    {
      unsigned long m = millis();
      if(m > lastTime + 6000)
      {
        setR(-255); setL(-255);
        delay(100);
        halt();
        lastTime = m;
      }
      t = 0;
    }
    else //if it's on the blue line and it doesn't see any claimed corner beacons, follow the line
    {
      int turnRightAmt = blueMoveSpeed * 0.2 * (blueLoc - 3);
      setR(blueMoveSpeed * 0.8 - turnRightAmt);
      setL(blueMoveSpeed * 0.7 + turnRightAmt);
    }
    blueLoc = getBlueLineLoc();
  }
}

double getBlueLineLoc()
{
  //classify what color the IR readers are on
  int IR[] = { readIr(1), readIr(2), readIr(3), readIr(4), readIr(5) };
  int irClassified[5];
  for(int i = 0; i < 5; i++)
  { irClassified[i] = classifyIR(IR[i]); }

  //count black and blue readings, and also sum up the total of the reading classification values
  int countBlack = 0; int countBlue = 0; double sum = 0.0;
  for(int i = 0; i < 5; i++)
  {
    if(irClassified[i] == 2)
    { countBlack++; sum+= i + 1; }
    if(irClassified[i] == 1)
    { countBlue++; sum+= i + 1; }
  }
  
  //if no clear blue line or too many black circle readings, return -1 (invalid)
  if(countBlack > 1 or (countBlue + countBlack) == 0) { return -1; }

  //turn towards area with highest number (darkest spot)
  return (sum/(countBlack + countBlue));
}

//0 = white, 1 = blue, 2 = black
int classifyIR(int ir)
{
  if(ir > 720 + random(20) and ir < 900 + random(50)) //blue
  { return 1; }
  else if (ir > 880) //white
  { return 0; }
  else //black
  { return 2; }
}

bool amOnBlueLineNow()
{
  int bNum = readBeaconWell();
  if(isCornerBeacon(bNum) and (XOR(bNum > 0, whiteTeam)))
  { return false; }
  
  //classify what color the IR readers are on
  int IR[] = { readIr(1), readIr(2), readIr(3), readIr(4), readIr(5) };
  int irClassified[5];
  for(int i = 0; i < 5; i++)
  { irClassified[i] = classifyIR(IR[i]); }
  
  //count black and blue readings in center
  int countBlack = 0; int countBlue = 0;
  for(int i = 1; i < 4; i++)
  {
    if(irClassified[i] == 2)
    { countBlack++; }
    if(irClassified[i] == 1)
    { countBlue++; }
  }
  
  if(countBlack < 2 and countBlue + countBlack > 1
    and IR[0] > 720 == 0 and IR[0] > 720)
  { return true; }
  else
  { return false; }
}

int cornerBeacons[] = {1, 2, 3, 4};
bool isCornerBeacon(int bNum)
{
  bNum = abs(bNum);
  for(int i = 0; i < 4; i++)
  {
    if(bNum == cornerBeacons[i])
    { return true; }
  }
  return false;
}

bool isHomeBeacon(int bNum)
{
  bNum = abs(bNum);
  return (((bNum == 2 or bNum == 3) and whiteTeam)
       or ((bNum == 1 or bNum == 4) and (not whiteTeam)));
}

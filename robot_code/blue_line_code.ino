/**
 * State for following blue line
 * Behaviors:
 * if see unclaimed bump beacon, slow down and go forward along blue line**
 * if see claimed bump beacon and time is almost up, go to go home state **
 * else if see claimed bump beacon, turn around**
 * if can't find blue line anymore, return to main state
 */
void followBlueLine()
{
  int blueLoc = getBlueLineLoc();
  while(blueLoc != -1)
  {
    int bNum = readBeaconWell();
    Serial.println("line!");
    if(isCornerBeacon(bNum))
    {
      if(XOR(bNum > 0, whiteTeam)) //if see unclaimed corner beacon, slow down and go forward along line
      {
        //
      }
      else //if see claimed bump beacon:
      {
        if(false) //if time is almost up, go home
        { headHome(bNum % 2 == 0); }
        else //otherwise, turn around
        {
          halt();
        }
      }
    }
    else //if it's on the blue line and it doesn't see any of the corner beacons, follow the line
    {
      //
    }
    blueLoc = getBlueLineLoc();
  }
}

int getBlueLineLoc()
{
  //classify what color the IR readers are on
  int IR[] = { readIr(1), readIr(2), readIr(3), readIr(4), readIr(5) };
  int irClassified[5];
  for(int i = 0; i < 5; i++)
  { irClassified[i] = classifyIR(IR[i]); }

  //count black and blue readings, and also sum up the total of the reading classification values
  int countBlack = 0; int countBlue = 0; int sum = 0;
  for(int i = 0; i < 5; i++)
  {
    if(irClassified[i] == 2)
    { countBlack++; }
    if(irClassified[i] == 1)
    { countBlue++; }
    sum += irClassified[i];
  }
  
  //if no clear blue line or too many black circle readings, return -1 (invalid)
  if(countBlack > 1 or countBlue == 0) { return -1; }

  //turn towards area with highest number (darkest spot)
  return (sum / 5);
}

//0 = white, 1 = blue, 2 = black
int classifyIR(int ir)
{
  if(ir > 720 + random(20) and ir < 900 + random(50)) //blue
  { return 1; }
  else if (ir > 800) //white
  { return 0; }
  else //black
  { return 2; }
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

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
    //if it's on the blue line and it doesn't see any of the corner beacons, follow the line
    Serial.println("line!");
    halt();
    blueLoc = getBlueLineLoc();
  }
}

int getBlueLineLoc()
{
  return 3;
}

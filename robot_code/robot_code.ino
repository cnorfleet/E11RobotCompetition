/**
 * robot code for the E11 competition
 * Caleb, Howard, and Lorelei
 * November 2017
 */

#define LEDpin 13
#define teamPin 3
boolean whiteTeam = false;
int gcMult = -1;

//IR reflectance thresholds
#define lineThreshold 790
#define circleThreshold 640

//white = 970 +- 10
//black circle = 590 +- 25
//blue line = 700 +- 70
//red line = indistinguishable from white  

//line following speeds
#define outSpeedR 1
#define outSpeedL 0.2
#define inSpeedL 0.7
#define inSpeedR -0.3

void setup()
{
  Serial.begin(9600);
  initMotors();
  initSensors();
  pinMode(LEDpin, OUTPUT);
  pinMode(teamPin, INPUT);
  digitalWrite(LEDpin, LOW);
  delay(200);
  whiteTeam = (digitalRead(teamPin) == LOW);
  if(whiteTeam) { gcMult = 1; }

  setR((int) (255 * 0.8));
  setL((int) (255 * 0.9));
  while(readIrAvg() > 620)
  { printAllSensors(); delay(1); }
  Serial.println("aaaaaaaa");
  setR((int) (255 * inSpeedR));
  setL((int) (255 * inSpeedL));
  delay(50);
  halt();
}

/**
 * Behavior list:
 * special: at start, go forward until find black circle (see start)**
 * if see unclaimed bump beacon, slow down and go forward along blue line**
 * if see claimed bump beacon, turn around**
 * if found blue line, follow it**
 * if on black circle, turn right to stay on circle
 * if lost, bank turn left
 */
 int t = 0;
void loop()
{
  if (t > 300)
  { printAllSensors(); t=0; } t++;
  
  double moveSpeed = 255.0;
  if(false) //if it sees the blue line
  {
    //do a thing
  }
  else if(readIrAvg() < 720 + random(100)) //if in circle, turn right
  {
    setR((int) (moveSpeed * inSpeedR));
    setL((int) (moveSpeed * inSpeedL));
    flashNextCode();
    
  }
  else //if lost, bank turn left
  {
    setR((int) (moveSpeed * outSpeedR));
    setL((int) (moveSpeed * outSpeedL));
    flashNextCode();
  }
  
  /*//get to far beacon #1 (as white team)://
  //behaviors:
  //if see claimed beacon, stop moving
  //if see unclaimed beacon, keep moving but go slower
  //if on line turn right
  //if lost, wide turn left
  boolean done = false;
  while(!done)
  {
    //setup
    int moveSpeed = 255;
    int beaconAt = readBeaconWell();
    Serial.print(beaconAt);
    int ir = 0;//readIrReflect();

    //react based on beacon at
    if(beaconAt == 3)
    { done = true; continue; }
    else if(beaconAt == -3)
    { moveSpeed = 150; flashCode(3); }
    
    //moved based on irSensor
    Serial.print(", "); Serial.print(ir); Serial.print("; ");
    if(ir > lineThreshold)
    {
      int speedL = (int) (inSpeed1 * moveSpeed);
      int speedR = (int) (inSpeed2 * moveSpeed);
      Serial.print(speedL); Serial.print(", "); Serial.println(speedR);
      setL((int) (inSpeed1 * moveSpeed));
      setR((int) (inSpeed2 * moveSpeed));
    }
    else
    {
      int speedL = (int) (outSpeed2 * moveSpeed);
      int speedR = (int) (outSpeed1 * moveSpeed);
      Serial.print(speedL); Serial.print("; "); Serial.println(speedR);
      setR((int) (outSpeed1 * moveSpeed));
      setL((int) (outSpeed2 * moveSpeed));
    }
  }
  while(true) //after done, just stop
  { halt(); delay(50); }*/
}

int codesToFlash[] = { 5, 6, 7, 8, 5, 6, 7, 8, 9 };
int curCodeIdx = 0;
//this takes ~8 milliseconds
void flashNextCode()
{
  flashCode(codesToFlash[curCodeIdx]);
  curCodeIdx++;
  if(curCodeIdx > 9)
  { curCodeIdx = 0; }
}

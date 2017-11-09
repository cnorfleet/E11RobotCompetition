/**
 * robot code for the E11 competition
 * Caleb, Howard, and Lorelei
 * November 2017
 */

#define LEDpin 13
#define teamPin 3
boolean whiteTeam;

//IR reflectance thresholds
#define startBoxThreshold 700
#define lineThreshold 790
#define circleThreshold 940

//line following speeds
#define outSpeed1 0.8
#define outSpeed2 -0.2
#define inSpeed1 1
#define inSpeed2 0.5

void setup()
{
  Serial.begin(9600);
  initMotors();
  initSensors();
  initServo();
  pinMode(LEDpin, OUTPUT);
  pinMode(teamPin, INPUT);
  digitalWrite(LEDpin, LOW);
  delay(200);
  whiteTeam = (digitalRead(teamPin) == LOW);
}

void loop()
{
  //get to far beacon #1 (as white team)://
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
    int ir = readIrReflect();

    //react based on beacon at
    if(beaconAt == 1)
    { done = true; continue; }
    else if(beaconAt == -1)
    { moveSpeed = 200; }
    
    //moved based on irSensor
    Serial.print(", "); Serial.println(ir);
    if(ir > lineThreshold)
    {
      setL((int) (inSpeed1 * moveSpeed));
      setR((int) (inSpeed2 * moveSpeed));
    }
    else
    {
      setR((int) (outSpeed1 * moveSpeed));
      setL((int) (outSpeed2 * moveSpeed));
    }
  }
  while(true) //after done, just stop
  { halt(); delay(50); }
}

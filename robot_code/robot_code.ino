/**
 * robot code for the E11 competition
 * Caleb, Howard, and Lorelei
 * November 2017
 */

/**
 * Behavior list: (divided amoung three (and a half) states)
 * special: at start, go forward until find black circle (see start)**
 * special: if at end of game and at one of the claimed beacons next to start, try to return to start **
 * if see unclaimed bump beacon, slow down and go forward along blue line**
 * if see claimed bump beacon, turn around**
 * if found blue line, follow it**
 * if on black circle, turn right to stay on circle
 * if lost, bank turn left
*/

#define LEDpin 13
#define teamPin 3
#define ninePin 2
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
#define blueSpeedL 0.6
#define blueSpeedR -0.4

void setup()
{
  Serial.begin(9600);
  initMotors();
  initSensors();
  pinMode(LEDpin, OUTPUT);
  pinMode(ninePin, OUTPUT);
  pinMode(teamPin, INPUT);
  digitalWrite(LEDpin, LOW);
  delay(200);
  whiteTeam = (digitalRead(teamPin) == LOW);
  if(whiteTeam) { gcMult = 1; }
  
  //start "state":
  //behavior (special): at start, go forward until it finds black circle
  /*setR((int) (255 * 0.8));
  setL((int) (255 * 0.9));
  while(readIrAvg() > 620)
  { printAllSensors(); delay(1); }
  Serial.println("aaaaaaaa");
  setR((int) (255 * inSpeedR));
  setL((int) (255 * inSpeedL));
  delay(50);*/
  halt();
}

/**
 * Main state ("loop")
 * Behaviors:
 * if found blue line, turn to follow it and switch to blue line state
 * if on black circle, turn right to stay on circle
 * if lost, bank turn left
 */
 int t = 0;
void loop()
{
  if (t > 300)
  { printAllSensors(); t=0; } t++;
  
  double moveSpeed = 255.0;
  if(false) //if currently on blue line, jump to blue line state
  {
    //write this code plz
  }
  else if((readIr(1) + readIr(2) + readIr(3))/3 < 720 + random(50)
    and ((readIr(4) > 720 + random(20)
    and readIr(4) < 900 + random(50))
    and (readIr(5) > 720 + random(20)
    and readIr(5) < 900 + random(50)))) //if it sees the blue line and is on black circle, turn right and go to blue line state
  {
    Serial.println("blue!");
    setR((int) (moveSpeed * blueSpeedR));
    setL((int) (moveSpeed * blueSpeedL));
    delay(500);
    followBlueLine(); //go to following blue line state
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
}

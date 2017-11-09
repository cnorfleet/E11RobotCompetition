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
    if(r < lineThreshold) //turn left
    { 
      //setR
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

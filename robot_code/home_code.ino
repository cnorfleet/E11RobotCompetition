/**
 *   The song played upon completing the game is the death sound effect from Super Mario
 *   Bros. The notes were transcribed into frequencies by hand by me from sheet music
 *   posted to http://www.mariopiano.com/mario-sheet-music-death-sound.html.
 */

/**
 * Go home (final/special) state
 * if at end of game and at one of the claimed beacons next to start, try to return to start **
 */
void headHome(bool rightSide) //state for heading home at end of game
{
  if(rightSide)
  {
    //turn towards box
    setR(0.1 * 255);
    setL(0.9 * 255);
    delay(450);
    //go to the box
    setR((int) (255 * 0.65));
    setL((int) (255 * 0.80));
  }
  else
  {
    //turn towards box
    setR(0.75 * 255);
    setL(0.1 * 255);
    delay(450);
    //go to the box
    setR((int) (255 * 0.55));
    setL((int) (255 * 0.95));
  }
  while(readIrAvg() > 900)
  { delay(1); }
  delay(300);
  halt();

  //play a song b/c yay
  playEndSong();
  while(true)
  { delay(1); }
}

int melody[] = {
  1047, 1109, 1175, -1,
  784, 1175, -1, 1175,
  1175, 1047, 988,
  784, 659, -1, 659,
  523
};
#define s 1000
int tempo[] = {
  s/16, s/16, s/8, 3*s/4,
  s/4, s/4, s/4, s/4,
  s/3, s/3, s/3,
  s/4, s/4, s/4, s/4,
  s/4, -1
};

void playEndSong()
{
  int totalTime = 0; int i = 0;
  int currentTime = 0;
  while (true)
  {
    if (currentTime > totalTime)
    {
      if (tempo[i] < 0) { noTone(buzzerPin); return; }
      totalTime += tempo[i];
      tone(buzzerPin, 0);
      delay(7);
      tone(buzzerPin, melody[i]);
      i++;
    }
    currentTime++;
    delay(1);
  }
}

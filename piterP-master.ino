/*
   importent stuff:

   the PIR sensor MUST be connected to pin 2
   the toching sensor MUST be connected to pin 3
*/
#include "Spider.h"

Spider Piter;
unsigned long RandNumber = 0;
bool Randombool = 1;
void setup()
{
  attachInterrupt(0, MoveDetected, HIGH);
  attachInterrupt(1, IHaveBeenToched, HIGH);

  Piter.Step(20, 20, 30);
}


void loop()
{
  RandNumber = random(10, 100);
  for (int i = 0; i < RandNumber; ++i)
  {
    Piter.Step();
    if (Piter.Blocked())
    {
      Randombool = random(0, 1);
      for (int t = 0; t < 5; ++t)
      {
        Piter.Step(Randombool, !Randombool);
      }
    }
  }
  Piter.Speak();
}


void MoveDetected()
{
  if (Piter.IsSleeping())
  {
    Piter.WakeUp();
  }
}

void IHaveBeenToched()
{
  Piter.GetDown();
}

void CheckIfYouNeedToSleepOrToAttracAttention()
{
  if (Piter.TimeSinceIHaveBeenToched() > 60 * 1000)
  {
    Piter.AttracAttention();
  }

  if (Piter.TimeSinceSomeoneWasHere() > 60 * 1000 * 3)
  {
    Piter.Sleep();
  }
}

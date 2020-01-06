/*importent stuff:

   the PIR sensor MUST be connected to pin 2
   the toching sensor MUST be connected to pin 3
*/
#include "Spider.h"

Spider Piter;

void setup()
{
  attachInterrupt(0, MoveDetected, HIGH);
  attachInterrupt(1, IHaveBeenToched, HIGH);

  Piter.Step(20, 20, 30);
}


void loop()
{

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

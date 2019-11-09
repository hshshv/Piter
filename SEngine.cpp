#include "Arduino.h"
#include "SEngine.h"

SEngine:: SEngine (int pin, bool normal)
{
  servo.attach(pin);
  Normal = normal; 
  servo.write(90);
}

SEngine:: SEngine (int pin)
{
  servo.attach(pin); 
  servo.write(90);
}

void SEngine:: Reverse()
{
	Normal = !Normal;
}

void SEngine:: SetPin(int pin)
{
	servo.attach(pin);
	servo.write(90);
	Degrees = 90;
}

void SEngine:: Goto(int Angles)
{
  Degrees = Angles;
  if (Normal)
  {
    servo.write(Angles);
  }
  else
  {
    servo.write(180 - Angles);
  }
}

void SEngine:: Move(int Angles)
{
  Degrees += Angles;
  if(Degrees > 180)
  {
    Degrees = 180%Degrees;
    if(Degrees == 0)
    {
      Degrees = 180; 
    }
  }

  Goto(Degrees);
}

int SEngine:: GetDegrees()
{
  return(Degrees);
}

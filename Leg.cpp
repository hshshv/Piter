#include "Arduino.h"
#include "Leg.h"

Leg:: Leg (int UpEnginePin, bool upnormal, int DownEnginePin, bool downnormal) :
  UpEngine(UpEnginePin, upnormal),
  DownEngine(DownEnginePin, downnormal)
{

}

void Leg:: SetSpeed(int newspeed)
{
  Speed = 1000 - newspeed;
}

void Leg:: Align()
{
  UpEngine.Goto(90);
  DownEngine.Goto(90);
}

void Leg:: Promote(int HorizenalAngles, int VerticalAngles)
{
  UpEngine.Move(VerticalAngles);
  delay(Speed);
  DownEngine.Move(HorizenalAngles);
  delay(Speed);
  UpEngine.Goto(90);
  delay(Speed);
}

void Leg:: DisPromote(int HorizenalAngles, int VerticalAngles)
{
  UpEngine.Move(VerticalAngles);
  delay(Speed);
  DownEngine.Move(-HorizenalAngles);
  delay(Speed);
  UpEngine.Goto(90);
  delay(Speed);
}

void Leg:: SwimAhed(int Angles)
{
  DownEngine.Goto(90 - Angles);
}

void Leg:: SwimBack(int Angles)
{
  DownEngine.Goto(90 + Angles);
}

void Leg:: Hello(int waves)
{
  UpEngine.Goto(120);
  delay(Speed);
  for (int i = 0; i < waves; ++i)
  {
    DownEngine.Goto(120);
    delay(Speed);
    DownEngine.Goto(60);
    delay(Speed);
  }
Align();
}

void Leg::Hello()
{
  Hello(2);
}

void Leg::Set(int upperAngles, int downAngles)
{
  UpEngine.Goto(upperAngles);
  DownEngine.Goto(downAngles);
}

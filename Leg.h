#ifndef Leg_h
#define Leg_h



#include "Arduino.h"
#include "SEngine.h"
class Leg
{
  private:
    int Speed = 100;
  public:
    SEngine UpEngine;
    SEngine DownEngine;
    Leg(int UpEnginePin, bool upnormal, int DownEnginePin, bool downnormal);
    void Promote(int HorizenalAngles, int VerticalAngles);
    void DisPromote(int HorizenalAngles, int VerticalAngles);
    void SwimAhed(int Angles);
    void SwimBack(int Angles);
    void Align();
    void Set(int upperAngles, int downAngles);
    void Hello(int waves);
    void Hello();
    void SetSpeed(int Speed);
};
#endif

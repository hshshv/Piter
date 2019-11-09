#ifndef UltrasonicSensor_h
#define UltrasonicSensor_h

#include "Arduino.h"
class UltrasonicSensor
{
  private:
    int TrigPin;
    int EchoPin;
    
  public:
    UltrasonicSensor(int Trig, int Echo);
    int StoppingDistance;
    float Get();
    bool Blocked();
};
#endif

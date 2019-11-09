#ifndef SEngine_h
#define SEngine_h



#include <Servo.h>
#include "Arduino.h"
class SEngine
{
  private:
    bool Normal = true;
    int Degrees = 90;
    Servo servo;
  public:
    SEngine(int pin, bool normal);
    SEngine(int pin);
    void Goto(int Angles);
    void Move(int Angles);
    int GetDegrees();
    void Reverse();
    void SetPin(int pin);
};
#endif

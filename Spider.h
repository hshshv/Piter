#ifndef Spider_h
#define Spider_h


#include "SoftwareSerial.h"
#include  "DFPlayer_Mini_Mp3.h"
#include "UltrasonicSensor.h"

#include "Arduino.h"
#include "Leg.h"


#define LegsPinsLength 8

class Spider
{
  private:
    UltrasonicSensor Up;
    UltrasonicSensor Down;
    float GetDistance();//V
    Leg RightFront;
    Leg RightBack;
    Leg LeftFront;
    Leg LeftBack;
    short EchoPin1;
    short TrigPin1;
    short EchoPin2;
    short TrigPin2;
    short TochSensorPin;
    short MoveingSensorPin;
    short LegsPins[LegsPinsLength] = {1, 2, 3, 4, 5, 6, 7, 8};
    long randNumber;
  public:
    Spider(short newEchoPin1, short newTrigPin1, short newEchoPin2, short newTrigPin2, short newTochSensorPin, short newMoveingSensorPin, const short ServoPins[], int Speed);
    Spider();
    void Step(int LeftAngles, int RightAngles, int VerticalAngles);///V
    void Step(int LeftAngles, int RightAngles);//V
    void Step(int VerticalAngles);///V
    void Step();
    //אולי להוסיף צעד אחורה או לא להוסיף ורק להתאים את סדר ההליכה למקרה שמעבירים לו מספר שלילי = אחורה
    void AttracAttention();
    void Hello();
    void MakeNois();
    void Sleep();
    void WakeUp();
    void Climb();
    void Print();////V
    void Speak();
    void AlignAllLegs();////V
    void Straight();
    float TopDistance();
    float BottomDistance();
    int DefaultVerticalAngles = 30;
    int DefaulthorizontalAngles = 30;
};
#endif

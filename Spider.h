#ifndef Spider_
#define Spider_


#include "Arduino.h"
#include "SoftwareSerial.h"//
#include "DFPlayer_Mini_Mp3.h"//they are bothe needed for the MP3 player
#include "UltrasonicSensor.h"

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
    short TochSensorPin = 3;
    short MoveingSensorPin = 2;
    short LegsPins[LegsPinsLength] = {1, 2, 3, 4, 5, 6, 7, 8};
    long randNumber;
    bool SleepModeIsOn = false;
    unsigned long LastTimeIHaveBeenToched = (unsigned long)millis();
    unsigned long LastTimeSomeoneWasHere = (unsigned long)millis();
  public:
    Spider(short newEchoPin1, short newTrigPin1, short newEchoPin2, short newTrigPin2, short newTochSensorPin, short newMoveingSensorPin, const short ServoPins[], int Speed);
    Spider();
    void Step(int LeftAngles, int RightAngles, int VerticalAngles);///V
    void Step(int LeftAngles, int RightAngles);//V
    void Step(int VerticalAngles);///V
    void Step();
    //אולי להוסיף צעד אחורה או לא להוסיף ורק להתאים את סדר ההליכה למקרה שמעבירים לו מספר שלילי = אחורה
    //לכאורה לא צריך, אפשר פשוט להעביר פרמטרים שליליים בתצורה הנוכחית של הקוד
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
    void GetDown();
    float TopDistance();
    float BottomDistance();
    int DefaultVerticalAngles = 30;
    int DefaulthorizontalAngles = 30;
    bool Toched();
    bool MoveDetect();
    bool IsSleeping();
    unsigned long TimeSinceIHaveBeenToched();
    unsigned long TimeSinceSomeoneWasHere();
};
#endif

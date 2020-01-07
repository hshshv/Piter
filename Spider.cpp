#include "Spider.h"

Spider:: Spider(short newEchoPin1, short newTrigPin1, short newEchoPin2, short newTrigPin2, short newTochSensorPin, short newMoveingSensorPin, const short ServoPins[], int Speed) :
  RightFront(ServoPins[0], false, ServoPins[1], true),
  RightBack(ServoPins[2], true, ServoPins[3], true),
  LeftFront(ServoPins[4], true, ServoPins[5], false),
  LeftBack(ServoPins[6], false, ServoPins[7], false),
  Up(newTrigPin1, newEchoPin1), Down(newTrigPin2, newEchoPin2)
{
  RightFront.SetSpeed(Speed);
  RightBack.SetSpeed(Speed);
  LeftFront.SetSpeed(Speed);
  LeftBack.SetSpeed(Speed);

  for (int i = 0; i < LegsPinsLength; ++i)
  {
    LegsPins[i] = ServoPins[i];
  }
  randomSeed(analogRead(5));
  EchoPin1 = newEchoPin1; TrigPin1 = newTrigPin1;  EchoPin2 = newEchoPin2; TrigPin2 = newTrigPin2; TochSensorPin = newTochSensorPin;  MoveingSensorPin = newMoveingSensorPin;
  Serial.begin (9600);
  mp3_set_serial (Serial); //set Serial for DFPlayer-mini mp3 module
  mp3_set_volume (10);
}

Spider:: Spider() :
  Spider(10, 11, 12, 13, 14, 15, (const short[]) {
  1, 2, 3, 4, 5, 6, 7, 8
}, 100)
{
  Serial.begin(9600);
  Print();
}

void Spider:: Step(int LeftAngles, int RightAngles, int VerticalAngles)//MAIN 'STEP'
{
  LeftBack.Promote(LeftAngles, VerticalAngles);

  LeftFront.Promote(LeftAngles, VerticalAngles);

  RightFront.SwimAhed(RightAngles);
  RightBack.SwimAhed(RightAngles);
  LeftFront.Align();
  LeftBack.Align();

  RightBack.Promote(RightAngles, VerticalAngles);

  RightFront.Promote(RightAngles, VerticalAngles);

  LeftFront.SwimAhed(LeftAngles);
  LeftBack.SwimAhed(LeftAngles);
  RightBack.Align();
  RightFront.Align();

  AlignAllLegs();
}

void Spider::Step(int LeftAngles, int RightAngles)
{
  if (DefaultVerticalAngles > 90 || DefaultVerticalAngles < 1)
  {
    DefaultVerticalAngles = 30;
  }
  Step(LeftAngles, RightAngles, DefaultVerticalAngles);
}

void Spider::Step(int VerticalAngles)
{
  if (DefaulthorizontalAngles > 90 || DefaulthorizontalAngles < 1)
  {
    DefaulthorizontalAngles = 30;
  }
  Step(DefaulthorizontalAngles, DefaulthorizontalAngles, VerticalAngles);
}

void Spider::Step(bool forward)
{
  if (DefaulthorizontalAngles > 90 || DefaulthorizontalAngles < 1)
  {
    DefaulthorizontalAngles = 30;
  }
  if (DefaultVerticalAngles > 90 || DefaultVerticalAngles < 1)
  {
    DefaultVerticalAngles = 30;
  }
  if(forward)
  {
    Step(DefaulthorizontalAngles, DefaulthorizontalAngles, DefaultVerticalAngles);
  }
  else
  {
    Step(-DefaulthorizontalAngles, -DefaulthorizontalAngles, DefaultVerticalAngles);
  }
}

void Spider::Step()
{
  Step(true);
}

void Spider:: AttracAttention()
{
  randNumber = random(1, 5);
  switch (randNumber)
  {
    case 1:  RightFront.Hello(); break;
    case 2:  RightBack.Hello(); break;
    case 3:  LeftFront.Hello(); break;
    case 4:  LeftBack.Hello(); break;
      break;
  }
  randNumber = random(11, 14);
  mp3_play (randNumber);
}

void Spider:: MakeNois()
{
  randNumber = random(2, 6);
  mp3_play (randNumber);
}

void Spider:: Speak()
{
  randNumber = random(6, 11);
  mp3_play (randNumber);
}

void Spider::AlignAllLegs()
{
  RightFront.Align();
  RightBack.Align();
  LeftFront.Align();
  LeftBack.Align();
}

void Spider:: Hello()
{
  mp3_play(1);
  RightFront.Hello(3);
}

void Spider:: Sleep()
{
  mp3_play (15);
  RightFront.UpEngine.Goto(130);
  RightBack.UpEngine.Goto(130);
  LeftFront.UpEngine.Goto(130);
  LeftBack.UpEngine.Goto(130);
  SleepModeIsOn = true;
}

void Spider:: WakeUp()//needs Mouth.h
{
  mp3_play (14);
  AlignAllLegs();
  SleepModeIsOn = false;
}

void Spider:: Climb()
{
  Straight();
  while (GetDistance() > 4)
  {
    Step(10, 10);
  }
  Straight();
  /*
     כל החלק של הטיפוס: הזזת הרגליים
  */
  AlignAllLegs();
}

void Spider:: Print()
{
  Serial.println("Connections list: \n");
  Serial.print("EchoPin 1: ");
  Serial.println(EchoPin1);
  Serial.print("TrigPin 1: ");
  Serial.println(TrigPin1);
  Serial.print("EchoPin 2: ");
  Serial.println(EchoPin2);
  Serial.print("TrigPin 2: ");
  Serial.println(TrigPin2);
  Serial.print("Toch Sensor Pin: ");
  Serial.println(TochSensorPin);
  Serial.print("Moveing Sensor Pin: ");
  Serial.println(MoveingSensorPin);
  Serial.print("\nLegs connections list: \n");
  Serial.print("Right Front Leg: \n\tupper motor pin: "); Serial.print(LegsPins[0]); Serial.print("\tdown motor pin: "); Serial.println(LegsPins[1]);
  Serial.print("Right Back Leg: \n\tupper motor pin: "); Serial.print(LegsPins[2]); Serial.print("\tdown motor pin: "); Serial.println(LegsPins[3]);
  Serial.print("Left Front Leg: \n\tupper motor pin: "); Serial.print(LegsPins[4]); Serial.print("\tdown motor pin: "); Serial.println(LegsPins[5]);
  Serial.print("Left Back Leg: \n\tupper motor pin: "); Serial.print(LegsPins[6]); Serial.print("\tdown motor pin: "); Serial.print(LegsPins[7]);
}

void Spider::Straight()///מוכן אך מפוקפק
{

  /*
    V    מדוד 2 מרחקים: 30 מעלות ימינה ולאחר מכן - 30 מעלות שמאלה.
    V    אם המרחק בצד ימין יותר קטן: פנה לאט לאט ימינה עד שתגיע למרחק הקטן ביותר מהקיר.
    אם המרחק בצד שמאל קטן יותר: פנה צעד אחד ימינה: >אם המרחק קטן יותר מהמרחק של צד שמאל, תמשיך לפנות ימינה עד שתגיע למרחק הקטן ביותר.
        >אם המרחק גדול יותר מהמרחק שמדדת בצד שמאל, פנה שמאלה לאט לאט, עד שתמצא את המרחק הקטן ביותר.
  */

  Step(30, -30);
  float RightDi = GetDistance();
  Step(-30, 30);
  Step(-30, 30);
  float LeftDi = GetDistance();
  if (RightDi < LeftDi - 1)
  {
    LeftDi = LeftDi + 0.1;
    while (!(GetDistance() > LeftDi))
    {
      LeftDi = GetDistance();
      Step(5, -5);
    }
    return;
  }
  else if (RightDi - 1 > LeftDi)
  {
    Step(5, -5);
    if (GetDistance() < LeftDi)
    {
      LeftDi = LeftDi + 0.1;
      while (!(GetDistance() > LeftDi))
      {
        LeftDi = GetDistance();
        Step(5, -5);
      }
    }
    else
    {
      RightDi = RightDi + 0.1;
      while (!(GetDistance() > RightDi))
      {
        RightDi = GetDistance();
        Step(-5, -5);
      }
    }
  }
}

void Spider::GetDown()
{
  RightFront.Set(RightFront.DownEngine.GetDegrees() , 150);//לבדוק שכל העסק אכן מתיישר כראוי ולא שחלק עולים וחלק יורדים, אמור להיות בסדר כי חלק מהסרוויים נהפכים עם רוורס בהתאם למיקומם וכו', אבל עדיין לבדוק
  RightBack.Set(RightBack.DownEngine.GetDegrees() , 150);
  LeftFront.Set(LeftFront.DownEngine.GetDegrees() , 150);
  LeftBack.Set(LeftBack.DownEngine.GetDegrees() , 150);
  Speak();
  delay(1000);
  AlignAllLegs();
}

float Spider::GetDistance()
{
  float upp =  Up.GetAvg();
  float don =  Down.GetAvg();
  if (upp > don)
  {
    return (don);
  }
  return (upp);
}

bool Spider::Toched()
{
  bool X = (digitalRead(TochSensorPin) == HIGH);
  if (X)
  {
    LastTimeIHaveBeenToched = (unsigned long)millis();
  }
  return (X);
}

bool Spider::MoveDetect()
{
  return (digitalRead(MoveingSensorPin) == HIGH);
}

bool Spider::IsSleeping()
{
  return (SleepModeIsOn);
}

unsigned long Spider::TimeSinceIHaveBeenToched()
{
  return ((unsigned long)millis() - LastTimeIHaveBeenToched);
}

unsigned long Spider::TimeSinceSomeoneWasHere()
{
  return((unsigned long)millis() - LastTimeSomeoneWasHere);
}

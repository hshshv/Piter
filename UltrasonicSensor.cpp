#include "UltrasonicSensor.h" 

UltrasonicSensor:: UltrasonicSensor (int Trig, int Echo)
{ 
  TrigPin = Trig;
  EchoPin = Echo;
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  StoppingDistance = 10;
}

bool UltrasonicSensor:: Blocked()
{
  if(StoppingDistance > 150)
  {
	 StoppingDistance = 10;
  }	 
  return((*this).Get() < StoppingDistance);
}

float UltrasonicSensor:: Get()
{
	digitalWrite(TrigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(TrigPin, LOW);
	return(pulseIn(EchoPin, HIGH) / 58.77);
}

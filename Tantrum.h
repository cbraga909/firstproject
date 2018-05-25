#include "Hunger.h"
#include "Affection.h"
#include "Sleep.h"

void Tantrum(int *tantrumLED);

void Tantrum(int *tantrumLED)
{
  if(HungerLevel()==0 && SleepLevel()==0 && AffectionLevel()==0)
  {
    digitalWrite(*tantrumLED,HIGH);
    //break;
  }
  else
  {
    digitalWrite(*tantrumLED,LOW);
  }
}

#ifndef _HUNGERH_
#define _HUNGERH_

#include "debouncer.h"

int increment=0;
unsigned long previousfeed=0;
unsigned long previousdec=0;
const long eatinterval=2000;
const long interval=4000;
boolean lastbutton=LOW;
boolean currentbutton=LOW;

void Hunger(int *button, int *hungerred, int *hungergreen, int *hungerblue);

void Hunger(int *button, int *hungerred, int *hungergreen, int *hungerblue)
{
  currentbutton=debouncehunger(lastbutton,button);
  unsigned long current=millis();
  if(lastbutton==LOW && currentbutton==HIGH && increment<=3 && current-previousfeed>=eatinterval)
  {
    previousfeed=current;
    increment++;
    if(increment>=4)
    {
      increment=4;
    }
  }
  if(currentbutton==LOW && current-previousdec>=interval && increment>=0 && current-previousfeed>=interval)
  {
    previousdec=current;
    increment--;
    if(increment<=0)
    {
      increment=0;
    }
  }
  switch(increment)
  {
    case 0:
    digitalWrite(*hungerred,HIGH);
    digitalWrite(*hungergreen,LOW);
    digitalWrite(*hungerblue,LOW);
    break;

    case 1:
    digitalWrite(*hungerred,HIGH);
    analogWrite(*hungergreen,40);
    digitalWrite(*hungerblue,LOW);
    break;

    case 2:
    digitalWrite(*hungerred,HIGH);
    analogWrite(*hungergreen,100);
    digitalWrite(*hungerblue,LOW);
    break;

    case 3:
    digitalWrite(*hungerred,LOW);
    digitalWrite(*hungergreen,LOW);
    digitalWrite(*hungerblue,HIGH);
    break;

    case 4:
    digitalWrite(*hungerred,LOW);
    digitalWrite(*hungergreen,HIGH);
    digitalWrite(*hungerblue,LOW);
    break;
  }
  lastbutton=currentbutton;
}

int HungerLevel(void);

int HungerLevel(void)
{
  return increment;
}

#endif

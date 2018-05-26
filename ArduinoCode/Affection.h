#ifndef _AFFECTIONH_
#define _AFFECTIONH_

int affectionIncrement=0;
unsigned long previouspet=0;
unsigned long previousaffection=0;
const long petinterval=4000;
const long affectioninterval=8000;


void Affection(int *PIR, int *affectionred, int *affectiongreen, int *affectionblue);
int AffectionLevel(int affectionIncrement);

void Affection(int *PIR, int *affectionred, int *affectiongreen, int *affectionblue)
{
  unsigned long currenttime=millis();
  if(analogRead(*PIR)>=100 && affectionIncrement<=3 && currenttime-previouspet>=petinterval)
  {
    previouspet=currenttime;
    affectionIncrement++;
    if(affectionIncrement>=4)
    {
      affectionIncrement=4;
    }
  }
  if(analogRead(*PIR)<100 && currenttime-previousaffection>=affectioninterval && affectionIncrement>=0 && currenttime-previouspet>=affectioninterval)
  {
    previouspet=currenttime;
    affectionIncrement--;
    if(affectionIncrement<=0)
    {
      affectionIncrement=0;
    }
  }
  switch(affectionIncrement)
  {
    case 0:
    digitalWrite(*affectionred,HIGH);
    digitalWrite(*affectiongreen,LOW);
    digitalWrite(*affectionblue,LOW);
    break;

    case 1:
    digitalWrite(*affectionred,HIGH);
    analogWrite(*affectiongreen,40);
    digitalWrite(*affectionblue,LOW);
    break;

    case 2:
    digitalWrite(*affectionred,HIGH);
    analogWrite(*affectiongreen,100);
    digitalWrite(*affectionblue,LOW);
    break;

    case 3:
    digitalWrite(*affectionred,LOW);
    digitalWrite(*affectiongreen,LOW);
    digitalWrite(*affectionblue,HIGH);
    break;

    case 4:
    digitalWrite(*affectionred,LOW);
    digitalWrite(*affectiongreen,HIGH);
    digitalWrite(*affectionblue,LOW);
    break;
  }
}

int AffectionLevel(void)
{
  return affectionIncrement;
}

#endif

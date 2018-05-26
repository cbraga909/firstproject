//sleepysongs.h
/*This header file contains the function that controls the pet's musical 
reaction to darkness and light.*/
#ifndef _SLEEPH_
#define _SLEEPH_

#include "pitches.h" //include header file containing pitches

//Initialize variables
int currentstate=1;
int k=0;
int val=0;
unsigned long previousSleepTime=0;
int sleepVal=4;
unsigned long previousSongTime=0;

//Array of pitches for lullaby, which will play when the pet is "put to bed" 
//Composer: Johannes Brahms'
//Piece: "Guten Abend, gute Nacht" aka "Brahms' Lullaby" aka "Cradle Song"; Op. 49, No. 4
int LullabyNotes[]={
  e4,e4,g4,e4,e4,g4,e4,g4,c5,b4,a4,a4,g4,d4,e4,f4,d4,d4,e4,f4,d4,f4,b4,a4,g4,b4,c5
};
//Array of beats for lullaby
//1=8th note, 2=quarter note, 3=dotted quarter note, 4=half note (3/4 meter)
double LullabyRhythm[]={
  1,1,4,1,1,4,1,1,2,3,1,2,2,1,1,2,2,1,1,4,1,1,1,1,2,2,4
};

//Array of pitches for morning song, which plays after the pet is "woken up" 
//Composer: Edvard Grieg
//Piece: "Morgenstemming" aka "Morning Mood" from Peer Gynt, Op. 23 and Peer Gynt Suite No. 1, Op.46
int MorningNotes[]={
  d5,b4,a4,g4,a4,b4,d5,b4,a4,g4,a4,b4,a4,b4,d5,b4,d5,e5,b4,e5,d5,b4,a4,g4
};
//Array of beats for morning song
//1=16th note, 2=8th note, 6=dotted half note (6/8 meter)
double MorningRhythm[]={
  2,2,2,2,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,2,2,2,2,6
};

//Function prototype. Note the pointers
void playSong(int *sensorPin, int *musicPin);
void sleepMeter(int *sensorPin, int *redLEDsleep, int *greenLEDsleep, int *blueLEDsleep);


void playSong(int *sensorPin, int *musicPin) //begin function
{
  int val=analogRead(*sensorPin); //read sensor pin
  //val<=100 ensures song plays when dark, and using currentstate prevents it from playing continuously
  //k allows iteration through arrays
  while(val<=50 && currentstate==1 && k<=sizeof(LullabyNotes)) 
  {
    unsigned long currentSongTime=millis();
    double noteDuration=(300*LullabyRhythm[k]); //set note duration
    tone(*musicPin,LullabyNotes[k]); //produce tone
    delay(noteDuration);
    noTone(*musicPin);
    k++;  
    
    val=analogRead(*sensorPin); //read the light sensor again

    //loop continues until k reaches the end of note array or the sensor is exposed to light
    if(k==28 || val>50) 
    {
      k=0; //reset k
      currentstate=2; //set currentstate to 2 so that lullaby will not play continously
      noTone(*musicPin); //turn off sound
      previousSleepTime=millis();
      break; 
    }  
  }

  //This loop will continue while sensor is exposesd to light and while currentstate is equal to 2
  while(val>50 && currentstate==2 && k<=sizeof(MorningNotes))
  {
    unsigned long currentSongTime=millis();
    double noteDuration=(180*MorningRhythm[k]); //set note duration for morning song
    tone(*musicPin,MorningNotes[k]); //generate tone
    delay(noteDuration);
    noTone(*musicPin);
    k++;
    val=analogRead(*sensorPin); //read sensor again
    
    //Once end of array is reached or sensor is covered, loop ends
    if(k==25 || val<=50)
    {
      k=0; //reset k
      currentstate=1; //set currentstate to 1 so loop will not continue to repeat
      noTone(*musicPin); //turn off sound
      previousSleepTime=millis();
      break;
    }
  }
}

void SleepMeter(int *sensorPin, int *redLEDsleep, int *greenLEDsleep, int *blueLEDsleep)
{
  int lightval=analogRead(*sensorPin);
  unsigned long currentSleepTime=millis();
  if(lightval<=50 && currentSleepTime-previousSleepTime>=4000 && sleepVal<4)
  {
    previousSleepTime=currentSleepTime;
    sleepVal++;
  }
  if(lightval>50 && currentSleepTime-previousSleepTime>=8000 && sleepVal>0)
  {
    previousSleepTime=currentSleepTime;
    sleepVal--;
  }
  switch(sleepVal)
  {
    case 0:
    digitalWrite(*redLEDsleep,HIGH);
    digitalWrite(*greenLEDsleep,LOW);
    digitalWrite(*blueLEDsleep,LOW);
    break;

    case 1:
    digitalWrite(*redLEDsleep,HIGH);
    analogWrite(*greenLEDsleep,40);
    digitalWrite(*blueLEDsleep,LOW);
    break;

    case 2:
    digitalWrite(*redLEDsleep,HIGH);
    analogWrite(*greenLEDsleep,100);
    digitalWrite(*blueLEDsleep,LOW);
    break;

    case 3:
    digitalWrite(*redLEDsleep,LOW);
    digitalWrite(*greenLEDsleep,LOW);
    digitalWrite(*blueLEDsleep,HIGH);
    break;

    case 4:
    digitalWrite(*redLEDsleep,LOW);
    digitalWrite(*greenLEDsleep,HIGH);
    digitalWrite(*blueLEDsleep,LOW);
    break;
  }
}

int SleepLevel(void);

int SleepLevel(void)
{
  return sleepVal;
}

#endif

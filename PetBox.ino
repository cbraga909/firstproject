//PetBox.c

/*This program controls an interactive pet box that must be fed, given attention, and put to bed
to keep its mood positive. Failure to do so can result in negative effects such as sad moods and tantrums*/

#include "Sleep.h" //include custom header file with song function
#include "Hunger.h"
#include "Affection.h"
#include "Tantrum.h"

int lightSensor=A0; //define light sensor pin
int speaker=3; //define speaker pin
int button=A1;
int PIR=A2;
int hungerred=7;
int hungergreen=9;
int hungerblue=8;
int affectionred=4;
int affectiongreen=5;
int affectionblue=6;
int sleepred=10;
int sleepgreen=11;
int sleepblue=12;
int tantrumpin=2;

void setup() {
  pinMode(button,INPUT);
  pinMode(hungerred,OUTPUT);
  pinMode(hungergreen,OUTPUT);
  pinMode(hungerblue,OUTPUT);
  pinMode(PIR,INPUT);
  pinMode(affectionred,OUTPUT);
  pinMode(affectiongreen,OUTPUT);
  pinMode(affectionblue,OUTPUT);
  pinMode(sleepred,OUTPUT);
  pinMode(sleepgreen,OUTPUT);
  pinMode(sleepblue,OUTPUT);
}

void loop() {
  playSong(&lightSensor,&speaker); //use song function from header file. & for memory address
  SleepMeter(&lightSensor,&sleepred,&sleepgreen,&sleepblue);
  Hunger(&button,&hungerred,&hungergreen,&hungerblue);
  Affection(&PIR,&affectionred,&affectiongreen,&affectionblue);
  Tantrum(&tantrumpin);
}

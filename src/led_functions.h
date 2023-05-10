#ifndef LED_FUNCTIONS_H
#define LED_FUNCTIONS_H

#include <Arduino.h>
#include <FastLED.h>
#include <hardware.h>


CRGB leds[NUMLEDS];
int counter=0;
uint8_t currentMood=0;
uint8_t cHue=0;

void initLeds(){

FastLED.addLeds<NEOPIXEL, LEDPIN>(leds, NUMLEDS);   
  FastLED.setBrightness(5);
  for(int i=0;i<NUMLEDS;i++){
  leds[i]=CRGB::DarkSlateGray;
  }
  set_max_power_in_volts_and_milliamps(5,50);
  FastLED.show();   
}

void friendly(){
fill_rainbow(leds,NUMLEDS,cHue,7);
}

void strobe(){
EVERY_N_MILLIS(50){
  fill_solid(leds,NUMLEDS,CRGB::White);
} 
EVERY_N_MILLIS(5){
  fadeToBlackBy(leds,NUMLEDS,100);
}
}

void angry(){
EVERY_N_MILLIS(300){
  fill_solid(leds,NUMLEDS,CRGB::Red);
} 
EVERY_N_MILLIS(5){
  fadeToBlackBy(leds,NUMLEDS,20);
}
}

void excited(){
fadeToBlackBy(leds,NUMLEDS,20);
int pos=random16(NUMLEDS);
leds[pos]+=CHSV(cHue+random8(64),200,255);
}

void happy(){
uint8_t bpm=100;
CRGBPalette16 palette = PartyColors_p;
uint8_t beat = beatsin8(bpm,64,255);
for(int i=0;i<NUMLEDS;i++){
  leds[i]=ColorFromPalette(palette,cHue+(i*2),beat-cHue+(i*10));
}
}

void sad(){
EVERY_N_MILLIS(3000){
  fill_solid(leds,NUMLEDS,CRGB::Blue);
  
} 
EVERY_N_MILLIS(10){

  fadeToBlackBy(leds,NUMLEDS,1);
}
}

void undecided(){
EVERY_N_MILLIS(1000){
  fill_solid(leds,NUMLEDS,CRGB::PaleVioletRed);
  
} 
EVERY_N_MILLIS(5){

  fadeToBlackBy(leds,NUMLEDS,5);
}
}

typedef void (*MoodList[])();
MoodList myMoods={friendly, strobe, angry, excited, happy, sad, undecided};



void showMood(int whichone){
  EVERY_N_MILLISECONDS(20){cHue++;}
  myMoods[whichone]();
  FastLED.show();  
}











void mood_friendly(){
  EVERY_N_MILLIS(20){
    fill_noise16(leds,NUMLEDS,3,1,1,1,1,15,0,millis()/50);
  }
  FastLED.show();  
}

void mood_excited(){
  EVERY_N_MILLIS(5){
    fill_noise16(leds,NUMLEDS,3,1,1,1,1,15,0,millis()/5);
  }
  FastLED.show();  
}

void mood_angry(){

EVERY_N_MILLIS(500){
  fill_solid(leds,NUMLEDS,CRGB::IndianRed);
} 

EVERY_N_MILLIS(5){

  fadeToBlackBy(leds,NUMLEDS,20);
}
 FastLED.show(); 
}

void mood_sad(){

EVERY_N_MILLIS(1000){
  fill_solid(leds,NUMLEDS,CRGB::RoyalBlue);
  
} 
EVERY_N_MILLIS(5){

  fadeToBlackBy(leds,NUMLEDS,5);
}
 FastLED.show(); 
}


void mood_obstacle(){

EVERY_N_MILLIS(100){
  fill_solid(leds,NUMLEDS,CRGB::Red);
} 

EVERY_N_MILLIS(5){

  fadeToBlackBy(leds,NUMLEDS,5);
}
 FastLED.show(); 
}

void setIndividual(int whichone, bool isOn){
  if(isOn){
  leds[whichone]=CRGB::Orange;
  FastLED.show();  
  }
  else{
     leds[whichone]=CRGB::Blue;
  FastLED.show();  
  }
}

#endif
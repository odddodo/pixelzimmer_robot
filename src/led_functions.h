#ifndef LED_FUNCTIONS_H
#define LED_FUNCTIONS_H

#include <Arduino.h>
#include <FastLED.h>
#include <hardware.h>


CRGB leds[NUMLEDS];
int counter=0;

void initLeds(){

FastLED.addLeds<NEOPIXEL, LEDPIN>(leds, NUMLEDS);   
  FastLED.setBrightness(5);
  for(int i=0;i<NUMLEDS;i++){
  leds[i]=CRGB::DarkSlateGray;
  }
  set_max_power_in_volts_and_milliamps(5,50);
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
    fill_noise16(leds,NUMLEDS,3,1,1,1,1,15,0,millis()/10);
  }
  FastLED.show();  
}

void mood_angry(){

EVERY_N_MILLIS(500){
  fill_solid(leds,NUMLEDS,CRGB::DarkRed);
} 

EVERY_N_MILLIS(5){

  fadeToBlackBy(leds,NUMLEDS,20);
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
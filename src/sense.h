#ifndef sense_h
#define sense_h

#include <hardware.h>
#include <Arduino.h>
#include <Ticker.h>
#include <led_functions.h>

bool sensorData[7]={0}; 

bool isOn=false;

void toggle(){
isOn=!isOn;
digitalWrite(SPS_IR_L,!isOn);
if(!isOn)sensorData[0]=digitalRead(IR_L);
digitalWrite(SPS_IR_L,isOn);
digitalWrite(SPS_IR_R,!isOn);
if(!isOn)sensorData[1]=digitalRead(IR_R);
digitalWrite(SPS_IR_R,isOn);
}

Ticker togglePwr(toggle,50);

void initSense(){
    pinMode(IR_F,INPUT);
    pinMode(IR_L,INPUT);
    pinMode(IR_R,INPUT);
    pinMode(IR_LINE_L,INPUT);
    pinMode(IR_LINE_R,INPUT);
    pinMode(IR_TOP_L,INPUT);
    pinMode(IR_TOP_R,INPUT);

    pinMode(SPS_IR_L,OUTPUT);
    pinMode(SPS_IR_R,OUTPUT);
    pinMode(SPS_IR_F,OUTPUT);
    pinMode(SPS_IR_L_L,OUTPUT);
    pinMode(SPS_IR_L_R,OUTPUT);

    togglePwr.start();
    }

void updateSense(){

   togglePwr.update();   
   setIndividual(0,sensorData[0]);
   setIndividual(1,sensorData[1]);
 
}
#endif
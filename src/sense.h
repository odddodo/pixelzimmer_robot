#ifndef sense_h
#define sense_h

#include <hardware.h>
#include <Arduino.h>
#include <Ticker.h>
#include <led_functions.h>

int s_PWR_addr[5] ={SPS_IR_L,SPS_IR_F,SPS_IR_R,SPS_IR_L_L,SPS_IR_L_R};
int s_addr[5]={IR_L,IR_F,IR_R,IR_L_L,IR_L_R};
bool sensorData[5]={0}; 
bool s_PWR_state[5]={0,1,1,1,1};
int sensorPWR_state=0;

void readSensorData(){ 
    for(int i=0;i<5;i++){ 
digitalWrite(s_PWR_addr[i],s_PWR_state[i]); 
if(s_PWR_state[i])sensorData[i]=digitalRead(s_addr[i]); 
s_PWR_state[i]=!s_PWR_state[i];
digitalWrite(s_PWR_addr[i],s_PWR_state[i]); 
    }
}

Ticker togglePwr(readSensorData,50);

void initSense(){
    pinMode(IR_F,INPUT);
    pinMode(IR_L,INPUT);
    pinMode(IR_R,INPUT);
    pinMode(IR_L_L,INPUT);
    pinMode(IR_L_R,INPUT);
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
   setIndividual(2,sensorData[2]);

}
#endif
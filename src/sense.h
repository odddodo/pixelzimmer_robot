#ifndef sense_h
#define sense_h

#include <hardware.h>
#include <Arduino.h>
#include <Ticker.h>
#include <led_functions.h>

enum sensorNames{
LEFT=0,
FRONT=1,
RIGHT=2,
L_LEFT=3,
L_RIGHT=4,
TOP_L=0,
TOP_R=1
};

sensorNames s_names=sensorNames::FRONT;

int s_PWR_addr[5] ={SPS_IR_L,SPS_IR_F,SPS_IR_R,SPS_IR_L_L,SPS_IR_L_R};
int s_addr[5]={IR_L,IR_F,IR_R,IR_L_L,IR_L_R};
bool sensorData[5]={0}; 
bool s_PWR_state[5]={0,1,1,1,1};
int sensorPWR_state=0;

int ambient_sensor_data[2]={0};

void readSensorData(){ 
    for(int i=0;i<5;i++){ 
digitalWrite(s_PWR_addr[i],s_PWR_state[i]); 
if(s_PWR_state[i])sensorData[i]=!digitalRead(s_addr[i]); 
s_PWR_state[i]=!s_PWR_state[i];
digitalWrite(s_PWR_addr[i],s_PWR_state[i]); 
    }
    ambient_sensor_data[TOP_L]=analogRead(IR_TOP_L);
    ambient_sensor_data[TOP_R]=analogRead(IR_TOP_R);
}

Ticker sense(readSensorData,50);

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

    sense.start();
    }

void updateSense(){

   sense.update();   
   //setIndividual(0,sensorData[0]);
   //setIndividual(1,sensorData[1]);
   //setIndividual(2,sensorData[2]);
//if(debug_sense)DEBUG("L:"+String(sensorData[sensorNames::LEFT])+" "+"F:"+String(sensorData[sensorNames::FRONT])+" "+"R:"+String(sensorData[sensorNames::RIGHT]));
//DEBUG(String(ambient_sensor_data[0]));
}

void stop_sense(){
    sense.pause();
     for(int i=0;i<5;i++){ 
digitalWrite(s_PWR_addr[i],0);  
     }  
}

void restart_sense(){
s_PWR_state[0]=1;
sense.resume();
}
#endif
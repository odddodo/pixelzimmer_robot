#ifndef drive_h
#define drive_h

#include <hardware.h>
#include <Arduino.h>
#include <debug.h>
#include <fuzzyLogic.h>
#include <globals.h>

const int pwmFreq=500;
const int pwmChannel_A=0;
const int pwmChannel_B=1;
const int resolution=8;

double AGGR_PWR(double sp, double trn, double hlt){
    return fuzzyOR(sp,fuzzyAND(trn,fuzzyNOT(hlt)));
}

void stopSTDBY(){
    digitalWrite(MOTOR_STDBY,LOW);
    digitalWrite(MOTOR_A_1,LOW);
    digitalWrite(MOTOR_A_2,LOW);
    digitalWrite(MOTOR_B_1,LOW);
    digitalWrite(MOTOR_B_2,LOW);
    digitalWrite(MOTOR_A_PWM,LOW);
    digitalWrite(MOTOR_B_PWM,LOW);
}

void initDrive(){
pinMode(MOTOR_A_1,OUTPUT);
pinMode(MOTOR_A_2,OUTPUT);
pinMode(MOTOR_B_1,OUTPUT);
pinMode(MOTOR_B_2,OUTPUT);
pinMode(MOTOR_A_PWM,OUTPUT);
pinMode(MOTOR_B_PWM,OUTPUT);
pinMode(MOTOR_STDBY,OUTPUT);

ledcSetup(pwmChannel_A,pwmFreq,resolution);
ledcSetup(pwmChannel_B,pwmFreq,resolution);
ledcAttachPin(MOTOR_A_PWM,pwmChannel_A);
ledcAttachPin(MOTOR_B_PWM,pwmChannel_B);

stopSTDBY();

DEBUG("drive setup!")
}




void drive(int speed_A, int speed_B){
    int dir_A=LOW;
    int dir_B=LOW;
    dir_A=(speed_A>0)?LOW:HIGH;
    dir_B=(speed_B>0)?LOW:HIGH;
    digitalWrite(MOTOR_STDBY,HIGH);
    digitalWrite(MOTOR_A_1,dir_A);
    digitalWrite(MOTOR_A_2,!dir_A);
    ledcWrite(pwmChannel_A,abs(speed_A));
    digitalWrite(MOTOR_B_1,dir_B);
    digitalWrite(MOTOR_B_2,!dir_B);
   ledcWrite(pwmChannel_B, abs(speed_B));
   

}


void fuzzyDrive(int fb, int trn, int maxSpeed){

float f_FWD =fuzzyGrade(fb,F_GRD_LO,F_GRD_HI);
float f_FWD_HLT=fuzzyTriangle(fb, F_TRI_LOL,F_TRI_HI,F_TRI_LOR);
float f_BCK=fuzzyRevGrade(fb,F_REV_GRD_LO,F_REV_GRD_HI);
float f_TRN_L=fuzzyRevGrade(trn, F_REV_GRD_LO, F_REV_GRD_HI);
float f_TRN_HLT=fuzzyTriangle(trn,F_TRI_LOL, F_TRI_HI, F_TRI_LOR);
float f_TRN_R=fuzzyGrade(trn,F_GRD_LO, F_GRD_HI);

//int MTL_speed = (int)(maxSpeed*AGGR_PWR(f_FWD,f_TRN_L,f_TRN_HLT))+(-maxSpeed)*AGGR_PWR(f_BCK,f_TRN_R,f_TRN_HLT);
//int MTR_speed=(int)(maxSpeed*AGGR_PWR(f_FWD,f_TRN_R,f_TRN_HLT))+(-maxSpeed)*AGGR_PWR(f_BCK,f_TRN_L,f_TRN_HLT);;

//DEBUG(String(fb)+"___"+String(f_FWD)+" "+String(f_FWD_HLT)+" "+String(f_BCK));

if(f_FWD_HLT>0.85&&f_TRN_HLT>0.85){
    stopSTDBY();
}
else{
int MTL_speed=maxSpeed*fuzzyOR(f_FWD,f_TRN_L)-maxSpeed*fuzzyOR(f_BCK,f_TRN_R);
int MTR_speed=maxSpeed*fuzzyOR(f_FWD,f_TRN_R)-maxSpeed*fuzzyOR(f_BCK,f_TRN_L);
drive(MTL_speed,MTR_speed);
//DEBUG(String(MTL_speed)+" "+String(MTR_speed));
}
}

#endif
#ifndef BEHAVIORS_H
#define BEHAVIORS_H

#include <drive.h>
#include <listening.h>
#include <sense.h>

long last_cmd_time;
long bored_timeout=20000;
bool bored=true;

int random_trn_vector=127;

void changeDirection(){
random_trn_vector=random(50,205);
}

Ticker roamFree(changeDirection,1000);


void initBehaviors(){
 roamFree.start();   
}

void idle(){
        if(sensorData[sensorNames::LEFT]||sensorData[sensorNames::FRONT]||sensorData[sensorNames::RIGHT]){
        mood_obstacle();
        }
        else{
        mood_friendly(); 
        }
        int comp_fb=constrain(127-sensorData[sensorNames::FRONT]*127,0,roam_speed);
        int comp_trn=constrain(random_trn_vector-sensorData[sensorNames::LEFT]*200+sensorData[sensorNames::RIGHT]*200,0,255);        
        fuzzyDrive(comp_fb,comp_trn,200);
        stopSmooth();
}

void manual(){
     updateListening();
if(myData.in_fb>160||myData.in_fb<100||myData.in_trn>160||myData.in_trn<100)
{
    last_cmd_time=millis(); 
    bored=false; 
    restart_sense();  
}  
if(millis()-last_cmd_time>bored_timeout){
    bored=true;
    stop_sense();
} 
    
    if(gotSomething&&!bored){
        updateSense();
        if(sensorData[sensorNames::LEFT]||sensorData[sensorNames::FRONT]||sensorData[sensorNames::RIGHT]){
        mood_obstacle();
        }
        else{
        mood_excited();
        }
        int comp_fb=constrain(myData.in_fb-sensorData[sensorNames::FRONT]*127,0,max_speed);
        int comp_trn=127;        
        fuzzyDrive(comp_fb,myData.in_trn,max_speed);    
    }
    else{
        
    stopSmooth(); 
    mood_friendly();  
    }
    
}

void follow_line(){
      updateSense();
      roamFree.update();
        if(sensorData[sensorNames::LEFT]||sensorData[sensorNames::FRONT]||sensorData[sensorNames::RIGHT]){
        mood_obstacle();
        }
        else{
        mood_friendly(); 
        }
        int comp_fb=constrain(roam_speed-sensorData[sensorNames::FRONT]*127,0,roam_speed);
        int comp_trn;
        if(flip_sensor_response){
        comp_trn=constrain(127+sensorData[sensorNames::L_LEFT]*100-sensorData[sensorNames::L_RIGHT]*100,0,255);  
        }
        else{
        comp_trn=constrain(127-sensorData[sensorNames::L_LEFT]*100+sensorData[sensorNames::L_RIGHT]*100,0,255);  
        }
              
        fuzzyDrive(comp_fb,comp_trn,220);
}

void follow_IR(){

}

void roam(){
    
      updateSense();
      roamFree.update();
        if(sensorData[sensorNames::LEFT]||sensorData[sensorNames::FRONT]||sensorData[sensorNames::RIGHT]){
        mood_obstacle();
        }
        else{
        mood_friendly(); 
        }
        int comp_fb=constrain(roam_speed-sensorData[sensorNames::FRONT]*200,0,roam_speed);
        int comp_trn;
        if(flip_sensor_response){
        comp_trn=constrain(random_trn_vector+sensorData[sensorNames::LEFT]*200-sensorData[sensorNames::RIGHT]*200,0,255); 
        }
        else{
        comp_trn=constrain(random_trn_vector-sensorData[sensorNames::LEFT]*200+sensorData[sensorNames::RIGHT]*200,0,255);   
        }     
        fuzzyDrive(comp_fb,comp_trn,200);
}

void behave(int mode){
    switch(mode){
        case 0:
        idle();
        break;
        case 1:
        roam();
        break;
        case 2:
        follow_line();
        break;
        case 3:
        manual();
        break;
        default:
        idle();
}
}


#endif
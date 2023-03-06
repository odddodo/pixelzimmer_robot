#ifndef BEHAVIORS_H
#define BEHAVIORS_H

#include <drive.h>
#include <listening.h>
#include <sense.h>

long last_cmd_time;
long bored_timeout=20000;
bool bored=true;

void idle(){

}

void manual(){
     updateListening();
if(myData.x>160||myData.x<100||myData.y>160||myData.y<100)
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
        int comp_fb=constrain(myData.x-sensorData[sensorNames::FRONT]*127,0,max_speed);
        int comp_trn=127;        
        updateDrive(comp_fb,myData.y);    
    }
    else{
        
    stopSmooth(); 
    mood_friendly();  
    }
    
}

void follow_line(){

}

void follow_IR(){

}

void roam(){

}

void behave(int mode){
    switch(mode){
        case 0:
        idle();
        break;
        case 1:
        manual();
        break;
        case 2:
        follow_line();
        break;
        case 3:
        follow_IR();
        break;
        default:
        roam();
}
}


#endif
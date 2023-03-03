#ifndef BEHAVIORS_H
#define BEHAVIORS_H

#include <drive.h>
#include <listening.h>
#include <sense.h>



void idle(){

}

void manual(){

    updateListening();
    updateSense();
    if(gotSomething){
        int comp_fb=constrain(myData.x-sensorData[sensorNames::FRONT]*127,0,255);
        int comp_trn=127;
DEBUG(String(comp_fb));
    updateDrive(comp_fb,myData.y);    
    }
    else{
    stopSmooth();
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
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
    updateDrive(myData.x,myData.y);
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
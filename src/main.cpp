#include <Arduino.h>
#include <behaviors.h>
#include <listening.h>
#include <sense.h>



void setup() {
initDrive();
initListening();
initLeds();
initSense();
initBehaviors();
}
 
void loop() {
    updateListening();
behave(myData.in_mode/64);

}
#include <Arduino.h>
#include <behaviors.h>
#include <listening.h>
#include <sense.h>



void setup() {
//delay(5000);
initDrive();
initListening();
initLeds();
initSense();
initBehaviors();
}
 
void loop() {
updateListening();
behave(myData.in_mode/51,myData.in_mood/36);

}
#include <Arduino.h>
#include <listening.h>
#include <sense.h>



void setup() {
initDrive();
initListening();
initLeds();
initSense();
}
 
void loop() {
updateListening();
updateSense();
}
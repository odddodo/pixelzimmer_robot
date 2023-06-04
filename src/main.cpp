#include <Arduino.h>
#include <behaviors.h>
#include <listening.h>
#include <sense.h>
#include <esp_task_wdt.h>



void setup() {
//delay(5000);
esp_task_wdt_init(WDT_TIMEOUT,true);
esp_task_wdt_add(NULL);

initDrive();
initListening();
initLeds();
initSense();
initBehaviors();
}
 
void loop() {
updateListening();
behave(myData.in_mode/51,myData.in_mood/36);

if(flag[0]==1&&flag[1]==1){
    flag[0]=0;
    flag[1]=0;
     esp_task_wdt_reset();
}
//delay(10);
}
#ifndef listening_h
#define listening_h

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <led_functions.h>
#include <debug.h>
#include <drive.h>

bool gotSomething=false;

long lastMessage=0;
long timeout=500;

typedef struct test_struct {
  int in_mode;
  int in_fb;
  int in_trn;
} test_struct;


test_struct myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));

  gotSomething=true;
  lastMessage=millis();
}


void initListening(){
  Serial.begin(115200);
      //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  DEBUG(WiFi.macAddress());
  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    DEBUG("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void updateListening(){
      if(gotSomething){
    
       
//DEBUG("received some data!");

  }

  if(millis()-lastMessage>timeout){
    gotSomething=false;
   stopSTDBY(); 
mood_angry();
//DEBUG("not getting the data!");
  }
}
#endif
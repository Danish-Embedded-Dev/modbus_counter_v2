/*
  MODULE live status 
  
  build 26 FEB 2023
  by M.Danish
  
*/

#include "hal.h"
#include "LiveStatus.h"   

//module online status instance
LiveStatus  ModuleStatus(STATUS_LED,1000);

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  while(!Serial);
  HAL_gpioInit(); 
}

unsigned long time_now = 0;
// the loop function runs over and over again forever
void loop() {

   if(Serial.available()>1){
      Serial.read();
      ModuleStatus.set();  //start led blink for 1000 ms 
   }

   if(millis()-time_now > 1000){
      time_now = millis();
      Serial.println("live");
   }

    ModuleStatus.process();  //handle process of module live activity
}

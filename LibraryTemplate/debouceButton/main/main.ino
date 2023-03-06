/*
  Button Pressed with 
  Debounce handling 
  
  build 26 FEB 2023
  by M.Danish
  
*/

#include "hal.h"
#include "ButtonDebounce.h"   

//button instance
ButtonDebounce  button1(INPUT_SW_1,1000);  //1000 ms debounce
ButtonDebounce  button2(INPUT_SW_2,500);  //500 ms debounce

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  while(!Serial);
  HAL_gpioInit(); 
}

unsigned long time_now = 0;
// the loop function runs over and over again forever
void loop() {

   if(millis()-time_now > 500){
      time_now = millis();
      Serial.print("live:");
      Serial.print(button1.getcount());
      Serial.print(",");
      Serial.println(button2.getcount());
   }

    button1.process();  //handle process of button1 activity
    button2.process();  //handle process of button2 activity
}

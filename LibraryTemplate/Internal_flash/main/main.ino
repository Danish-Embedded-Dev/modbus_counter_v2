#include "conf.h" 
#include "internal_flash.h"

EEPROM_OPERATION  internal_flash;

void setup() {
  Serial.begin(9600);
  while(!Serial); 
  //initialize internal flash for storage
  internal_flash.begin();

  //set structure to internal flash
//  internal_flash.set_struct_var(&default_var,sizeof(default_var));  

  //get structure from internal flash
  if(internal_flash.get_struct_var(&running_var,sizeof(running_var))){
    Serial.println("EEPROM_CHECK : OK"); 
  }else{
    Serial.println("EEPROM_CHECK : ERR"); 
  }
}

// the loop function runs over and over again forever
void loop() { 
}

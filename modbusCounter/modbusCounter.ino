//void  Init_Modbus_Var() {
//  
//  //Assign the modbus device ID.
//  regBank.setId(running_val.device_id);
//
//  /*
//    modbus registers follow the following format
//    00001-09999  Digital Outputs, A master device can read and write to these registers
//    10001-19999  Digital Inputs, A master device can only read the values from these registers
//    30001-39999  Analog Inputs, A master device can only read the values from these registers
//    40001-49999  Analog Outputs, A master device can read and write to these registers
//
//    Analog values are 16 bit unsigned words stored with a range of 0-32767
//    Digital values are stored as bytes, a zero value is OFF and any nonzer value is ON
//
//    It is best to configure registers of like type into contiguous blocks.  this
//    allows for more efficient register lookup and and reduces the number of messages
//    required by the master to retrieve the data
//  */
//
//  /*
//   * No coil used in this module
//   */
//  //Add Digital Output registers 00001-00016 to the register bank
//  //  regBank.add(1);
//  //  regBank.add(2); 
//
//  //Add Digital Input registers 10001-10008 to the register bank
//  //  regBank.add(10001);
//  //  regBank.add(10002); 
//
//  //Add holding registers 30001-10010 to the register bank
//  /*
//   * use for default configuration
//   */
//  regBank.add(40001); // use for device_id
//  regBank.add(40002); // use for modbus configuration
//  regBank.add(40003); // use for modbus baudrate 
//  regBank.add(40004); // use for network timeout 
//  regBank.add(40005); // use for debouncing time 
//  regBank.add(40006); // use for restart the device
//  regBank.add(40007); // use for epoch LSB
//  regBank.add(40008); // use for epoch MSB
//  
//  //Add Input registers 40001-40020 to the register bank
//  /*
//   * Use for counter value 
//   */
//   
//  regBank.add(30011);  //count_1a
//  regBank.add(30012);  //count_1b
//  regBank.add(30013);  //count_1c
//  regBank.add(30014);  //C1_lastEvent epoch LSB  //follow big endian
//  regBank.add(30015);  //C1_lastEvent epoch MSB
//  
//  regBank.add(30021);  //count_2a 
//  regBank.add(30022);  //count_2b
//  regBank.add(30023);  //count_2c
//  regBank.add(30024);  //C2_lastEvent epoch LSB  //follow little endian
//  regBank.add(30025);  //C2_lastEvent epoch MSB
//
//  /*
//    Assign the modbus device object to the protocol handler
//    This is where the protocol handler will look to read and write
//    register data.  Currently, a modbus slave protocol handler may
//    only have one device assigned to it.
//  */
//  _device = &regBank;
//
//  // Initialize the serial port for coms at 9600 baud
//  setBaud(running_val.mod_baud,running_val.mod_config);//start Modbus communication with store configuration 
//
//} 
#include "main.h"

/**
    update modbus holding and input register with eeprom store variable
*/

void update_counter(void) {
  //put some data into the registers

  //add coil register
  //  regBank.set(1, 1);           //no coil status used in this module
  //  regBank.set(2, 1);

  //input status register
  //  regBank.set(10001, 1);      //no input status used in this module
  //  regBank.set(10002, 1);


  //adding holding register
  regBank.set(40001, running_val.device_id);
  regBank.set(40002, running_val.mod_config);
  regBank.set(40003, running_val.mod_baud);
  regBank.set(40004, running_val.net_timeout);
  regBank.set(40005, running_val.debounce_tm);
  regBank.set(40006, 0); //zero for normal and 1 for restart
  unsigned long rtc_time = getEpoch();
  regBank.set(40007, int((rtc_time)&0xFFFF));     //put Epoch LSB 
  regBank.set(40008, int((rtc_time>>16)&0xFFFF)); //put Epoch MSB
  
  //adding input register
  regBank.set(30011, running_val.count_1a);
  regBank.set(30012, running_val.count_1b);
  regBank.set(30013, running_val.count_1c);
  regBank.set(30014, int((running_val.lst_epoch_c1)&0xFFFF));  //put last event c_1 Epoch LSB 
  regBank.set(30015, int((running_val.lst_epoch_c1>>16)&0xFFFF));  //put last event c_1 Epoch MSB 

  regBank.set(30021, running_val.count_2a);
  regBank.set(30022, running_val.count_2b);
  regBank.set(30023, running_val.count_2c);
  regBank.set(30014, int((running_val.lst_epoch_c2)&0xFFFF));    //put last event c_2 Epoch LSB 
  regBank.set(30015, int((running_val.lst_epoch_c2>>16)&0xFFFF));  //put last event c_2 Epoch MSB 

}
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

  //Assign the modbus device ID.  
  regBank.setId(1);

/*
modbus registers follow the following format
00001-09999  Digital Outputs, A master device can read and write to these registers
10001-19999  Digital Inputs, A master device can only read the values from these registers
30001-39999  Analog Inputs, A master device can only read the values from these registers
40001-49999  Analog Outputs, A master device can read and write to these registers 

Analog values are 16 bit unsigned words stored with a range of 0-32767
Digital values are stored as bytes, a zero value is OFF and any nonzer value is ON

It is best to configure registers of like type into contiguous blocks.  this
allows for more efficient register lookup and and reduces the number of messages
required by the master to retrieve the data
*/

//Add Digital Output registers 00001-00016 to the register bank
  regBank.add(1);
  regBank.add(2);
  regBank.add(3);
  regBank.add(4);
  regBank.add(5);
  regBank.add(6);
  regBank.add(7);
  regBank.add(8);
  regBank.add(9);
  regBank.add(10);
  regBank.add(11);
  regBank.add(12);
  regBank.add(13);
  regBank.add(14);
  regBank.add(15);
  regBank.add(16);

//Add Digital Input registers 10001-10008 to the register bank
  regBank.add(10001);  
  regBank.add(10002);  
  regBank.add(10003);  
  regBank.add(10004);  
  regBank.add(10005);  
  regBank.add(10006);  
  regBank.add(10007);  
  regBank.add(10008);  

//Add Analog Input registers 30001-10010 to the register bank
  regBank.add(30001);  
  regBank.add(30002);  
  regBank.add(30003);  
  regBank.add(30004);  
  regBank.add(30005);  
  regBank.add(30006);  
  regBank.add(30007);  
  regBank.add(30008);  
  regBank.add(30009);  
  regBank.add(30010);  

//Add Analog Output registers 40001-40020 to the register bank
  regBank.add(40001);  
  regBank.add(40002);  
  regBank.add(40003);  
  regBank.add(40004);  
  regBank.add(40005);  
  regBank.add(40006);  
  regBank.add(40007);  
  regBank.add(40008);  
  regBank.add(40009);  
  regBank.add(40010);  
  regBank.add(40011);  
  regBank.add(40012);  
  regBank.add(40013);  
  regBank.add(40014);  
  regBank.add(40015);  
  regBank.add(40016);  
  regBank.add(40017);  
  regBank.add(40018);  
  regBank.add(40019);  
  regBank.add(40020);  

/*
Assign the modbus device object to the protocol handler
This is where the protocol handler will look to read and write
register data.  Currently, a modbus slave protocol handler may
only have one device assigned to it.
*/
  slave._device = &regBank;  

// Initialize the serial port for coms at 9600 baud  
  slave.setBaud(9600);   
}

unsigned test = 0 ;
// the loop function runs over and over again forever
void loop() { 
  //put some data into the registers
  regBank.set(1, 1);  
  regBank.set(2, 1);  
  regBank.set(3, 0);  
  regBank.set(4, 1);  
  regBank.set(5, 1);  
  regBank.set(6, 0);  
  regBank.set(7, 1);  
  regBank.set(8, 0);  

  regBank.set(10001, 1);
  regBank.set(10002, 1);  
  regBank.set(10003, 1);  
  regBank.set(10004, 1);  
  regBank.set(10005, 0);  
  regBank.set(10006, 0);  
  regBank.set(10007, 0);  
  regBank.set(10008, 0);  
  
  regBank.set(30001,1);
  regBank.set(30002,2);
  regBank.set(30003,2);
  regBank.set(30004,4);
  regBank.set(30005,5);
  regBank.set(30006,6);
  regBank.set(30007,7);
  regBank.set(30008,8);
  regBank.set(30009,9);
  regBank.set(30010,10);
  
  regBank.set(40001,  running_var.device_id);   //holding registers
  regBank.set(40002,  running_var.mod_config);  
  regBank.set(40003,  running_var.mod_baud);  
  regBank.set(40004,  running_var.net_timeout);  
  regBank.set(40005,  running_var.debounce_tm);  
  regBank.set(40006,  int((running_var.count_1)&0xFFFF));          //LSB
  regBank.set(40007,  int((running_var.count_1>>16)&0xFFFF));      //MSB
  regBank.set(40008, 0);  

  
 while(1)
  { 
    update_counter();
    if(millis()-test>1000){
      test = millis();       
      running_var.count_1++;
    }
    
    slave.run();  
  }
}

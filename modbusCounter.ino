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


void setup() {
  Serial.begin(9600);
  while(!Serial); 
  
#ifdef INTERNAL_EEPROM_ENABLE   
  //initialize internal flash for storage
  internal_flash.begin();

  //set structure to internal flash
  //internal_flash.set_struct_var(&default_var,sizeof(default_var));  

  //get structure from internal flash
  if(internal_flash.get_struct_var(&running_var,sizeof(running_var))){
    Serial.println("EEPROM_CHECK : OK"); 
  }else{
    Serial.println("EEPROM_CHECK : ERR"); 
  }
#endif//INTERNAL_EEPROM_ENABLE

#ifdef  RESET_STATUS
  //check the reset cause
  uint32_t rcc_csr_value = RCC_BASE->CSR;

  if ((rcc_csr_value & RCC_CSR_PORRSTF) != 0) { // POR/PDR reset
    // if Power on reset then reset  variable to zero
    SRAM_Var[_cnt_1]     = 0;
    SRAM_Var[_cnt_2]     = 0; 
  } else {
    running_var.count_1 = SRAM_Var[_cnt_1];
    running_var.count_2 = SRAM_Var[_cnt_2]; 
  }
  //  } else if ((rcc_csr_value & RCC_CSR_PINRSTF) != 0)  {// NRST pin reset
  //  } else if ((rcc_csr_value & RCC_CSR_SFTRSTF) != 0)  {// software reset 
  //  } else if ((rcc_csr_value & RCC_CSR_IWDGRSTF) != 0) {// independent watchdog reset 
  //  } else if ((rcc_csr_value & RCC_CSR_WWDGRSTF) != 0) {// window watchdog reset    
  //  } else if ((rcc_csr_value & RCC_CSR_LPWRRSTF) != 0) {// low-power reset
  //  }

  // Clear the reset flags in the RCC_CSR register
  //with Reset Management Value Flag
  RCC_BASE->CSR |= RCC_CSR_RMVF;
  
#endif//RESET_STATUS

#ifdef MODBUS_COUNTER
  //Pins Configuration
  gpioInit();
  
  //Assign the modbus device ID.  
  regBank.setId(1);
  init_reg();
  /*
  Assign the modbus device object to the protocol handler
  This is where the protocol handler will look to read and write
  register data.  Currently, a modbus slave protocol handler may
  only have one device assigned to it.
  */
  slave._device = &regBank;  

// Initialize the serial port for coms at 9600 baud  
  slave.setBaud(9600);  
#endif //MODBUS_COUNTER

}

unsigned test = 0 ;
// the loop function runs over and over again forever
void loop() { 

#ifdef  MODBUS_COUNTER    
  //put some data into the registers
    update_counter_reg();

    //setting led if there is any command comes
//    if(Serial2.available()>1){  //we are using Serial2 for modbus communication  
//      ModuleStatus.set();     //start led active for ACTIVE_TIME in ms 
//     }
   
    if(millis()-test>1000){
      test = millis();       
      running_var.count_1++;
    }
    
    button1.process();       //handle process of button1 activity
    button2.process();       //handle process of button2 activity
    slave.run();             //handle process of modbus module activity
    ModuleStatus.process();  //handle process of module live activity
#endif//MODBUS_COUNTER   

#ifdef INTERNAL_RTC_ENABLE
  SRAM_Var[_cnt_1]  =  running_var.count_1; //update sram variable
  SRAM_Var[_cnt_2]  =  running_var.count_2; //update sram variable
#endif//INTERNAL_RTC_ENABLE
}

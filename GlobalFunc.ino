/*
 * pin configuration 
 * setting pin as input or output
 */
void gpioInit()
{
  
   //make output for status led
   pinMode(STATUS_LED,OUTPUT);

   //make input pullup
   pinMode(INPUT_SW_1,INPUT_PULLUP);
   pinMode(INPUT_SW_2,INPUT_PULLUP);
}
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
void init_reg(void) {
  
//Add Digital Output registers 00001-00016 to the register bank
  regBank.add(1);      //for relay_1
  regBank.add(2);      //for relay_2

//Add Digital Input registers 10001-10008 to the register bank
  regBank.add(10001);  //for switch_1
  regBank.add(10002);  //for switch_2

//Add Analog Input registers 30001-10010 to the register bank
  regBank.add(30001);   // for epochtime (LSB)
  regBank.add(30002);   // for epochtime (MSB)
  regBank.add(30003);   // for count_1 (LSB)     
  regBank.add(30004);   // for count_1 (MSB)     
  regBank.add(30005);   // for count_2 (MSB)      
  regBank.add(30006);   // for count_2 (MSB)     
  
//Add Analog Output registers 40001-40020 to the register bank
  regBank.add(40001);   // for device_id
  regBank.add(40002);   // for serial configuration
  regBank.add(40003);   // for serial baud rate
  regBank.add(40004);   // for active led timeout period
  regBank.add(40005);   // for input switch debounce period
  regBank.add(40006);   // for reset the device
  regBank.add(40007);   // for epochtime (LSB)
  regBank.add(40008);   // for epochtime (MSB)
  regBank.add(40009);   // for count_1 (LSB)    default (0)
  regBank.add(40010);   // for count_1 (MSB)    default (0)
  regBank.add(40011);   // for count_2 (MSB)    default (0)
  regBank.add(40012);   // for count_2 (MSB)    default (0)
}
  
/**
    update modbus holding and input register with eeprom store variable
*/

void update_counter_reg(void) {
  //put some data into the registers
  
  regBank.set(1, 1);        //show relay_1 state
  regBank.set(2, 1);        //show relay_2 state 

  regBank.set(10001, 1);    //show input switch current state 
  regBank.set(10002, 1);    //show input switch current state
  
  regBank.set(30001, LSB_CAST(rtc.getTime()));            // for epochtime internal rtc (LSB)
  regBank.set(30002, MSB_CAST(rtc.getTime()));            // for epochtime internal rtc (MSB)
  regBank.set(30003, LSB_CAST(button1.getcount()));       // for counter 1 (LSB)
  regBank.set(30004, MSB_CAST(button1.getcount()));       // for counter 1 (MSB)
  regBank.set(30005, MSB_CAST(button2.getcount()));       // for counter 2 (LSB)
  regBank.set(30006, MSB_CAST(button2.getcount()));       // for counter 2 (MSB) 

  //holding registers
  regBank.set(40001,  running_var.device_id);              // for device id 
  regBank.set(40002,  running_var.mod_config);             // for serial configuration
  regBank.set(40003,  running_var.mod_baud);               // for serial baud rate
  regBank.set(40004,  running_var.net_timeout);            // for active led timeout period
  regBank.set(40005,  running_var.debounce_tm);            // for input switch debounce period
  regBank.set(40006,  NO_RESET_REQ);                       // show reset = false in normal state
  regBank.set(40007,  NORMAL_STATE);                       // for epochtime (LSB)   
  regBank.set(40008,  NORMAL_STATE);                       // for epochtime (MSB)
  regBank.set(40009,  NORMAL_STATE);                       // for count_1 (LSB)     
  regBank.set(40010,  NORMAL_STATE);                       // for count_1 (MSB)     
  regBank.set(40011,  NORMAL_STATE);                       // for count_2 (LSB)     
  regBank.set(40012,  NORMAL_STATE);                       // for count_2 (MSB)    
}


/**
    if user modify the configuration variable then save value to EEPROM
    @Returns: if eeprom update then true else false
*/
bool update_holdingReg() {
  bool _update = false ;

  //update device id if change by  modbus master
  if (running_var.device_id != slave._device->get(40001)) {
    running_var.device_id =  slave._device->get(40001); 
    _update = true;
  }

  //update modbus configuration if change by  modbus master
  if (running_var.mod_config != slave._device->get(40002)) {
    switch (slave._device->get(40002)) {
      case 0:
        // set to SERIAL wordlenght = 8 parity = none stop bits = 1
        running_var.mod_config = SERIAL_8N1;
        regBank.set(40002, SERIAL_8N1);
        break;
      case 32:
        // set to SERIAL wordlenght = 8 parity = none stop bits = 2
        running_var.mod_config = SERIAL_8N2;
        regBank.set(40002, SERIAL_8N2);
        break;
      case 8:
        // set to SERIAL wordlenght = 9 parity = none stop bits = 1
        running_var.mod_config = SERIAL_9N1;
        regBank.set(40002, SERIAL_9N1);
        break;
      case 40:
        // set to SERIAL wordlenght = 9 parity = none stop bits = 2
        running_var.mod_config = SERIAL_9N2;
        regBank.set(40002, SERIAL_9N2);
        break;
      case 10:
        // set to SERIAL wordlenght = 8 parity = even stop bits = 1
        running_var.mod_config = SERIAL_8E1;
        regBank.set(40002, SERIAL_8E1);
        break;
      case 42:
        // set to SERIAL wordlenght = 8 parity = even stop bits = 2
        running_var.mod_config = SERIAL_8E2;
        regBank.set(40002, SERIAL_8E2);
        break;
      case 11:
        // set to SERIAL wordlenght = 8 parity = old stop bits = 1
        running_var.mod_config = SERIAL_8O1;
        regBank.set(40002, SERIAL_8O1);
        break;
      case 43:
        // set to SERIAL wordlenght = 8 parity = old stop bits = 2
        running_var.mod_config = SERIAL_8O2;
        regBank.set(40002, SERIAL_8O2);
        break;
      default: //use if master modbus enter wrong data
        // set to SERIAL wordlenght = 8 parity = none stop bits = 1
        regBank.set(40002, SERIAL_8N1);
    }
 
    _update = true;
  }

  //update modbus baud rate if change by  modbus master
  if (running_var.mod_baud != slave._device->get(40003)) {
    switch (slave._device->get(40003)) {
      case 1:
        // set to 2400 baud
        running_var.mod_baud = 2400;
        regBank.set(40003, 2400);
        break;
      case 2:
        // set to 4800 baud
        running_var.mod_baud = 4800;
        regBank.set(40003, 4800);
        break;
      case 3:
        // set to 9600 baud
        running_var.mod_baud = 9600;
        regBank.set(40003, 9600);
        break;
      case 4:
        // set to 19200 baud
        running_var.mod_baud = 19200;
        regBank.set(40003, 19200);
        break;
      case 5:
        // set to 38400 baud
        running_var.mod_baud = 38400;
        regBank.set(40003, 38400);
        break;
    }
 
    _update = true;
  }

  //update network timeout if change by modbus master
  if (running_var.net_timeout != slave._device->get(40004)) {
    running_var.net_timeout = slave._device->get(40004); 
    _update = true;
  }

  //update debouncing time if change by modbus master
  if (running_var.debounce_tm != slave._device->get(40005)) {
    running_var.debounce_tm = slave._device->get(40005); 
    _update = true;
  }


  //set epoch value from modbus protocol
  //always add MSB first then LSB 
  
   if (slave._device->get(40008) != NORMAL_STATE) { //40008 (MSB) 
    rtc.setTime(MSB_SHIFT(slave._device->get(40008)));  
    _update = true;
  }
  
   if (slave._device->get(40007) != NORMAL_STATE) { //40007 (LSB) 
    uint32_t current_epoch  = rtc.getTime();
    current_epoch &= 0xFFFF0000;  // Clear the lower 16 bits
    current_epoch |= LSB_SHIFT(slave._device->get(40007));  // Set the lower 16 bits to the new value 
    rtc.setTime(current_epoch);  
    _update = true;
  }

  
  //set count_1 from modbus protocol

   if (slave._device->get(40010) != NORMAL_STATE) { //40010 (MSB)
    button1.setcount(MSB_SHIFT(slave._device->get(40010)));  
    _update = true;
  }

  
  if (slave._device->get(40009) != NORMAL_STATE) { //40009 (LSB) 
    uint32_t current_count  = button1.getcount();
    current_count &= 0xFFFF0000;  // Clear the lower 16 bits
    current_count |= LSB_SHIFT(slave._device->get(40009));  // Set the lower 16 bits to the new value 
    button1.setcount(current_count);  
    _update = true;
  }

   //set count_2 from modbus protocol

   if (slave._device->get(40012) != NORMAL_STATE) { //40012 (MSB)
    button2.setcount(MSB_SHIFT(slave._device->get(40012)));  
    _update = true;
  }

  
  if (slave._device->get(40011) != NORMAL_STATE) { //400011 (LSB)
    uint32_t current_count  = button1.getcount();
    current_count &= 0xFFFF0000;  // Clear the lower 16 bits
    current_count |= LSB_SHIFT(slave._device->get(40011));  // Set the lower 16 bits to the new value 
    button2.setcount(current_count); 
    _update = true;
  }


  return _update;
} 

///**
//    if user modify the configuration to take action
//*/
void response_holdingReg() {

  //restart the device if user input 1
  if ( slave._device->get(40006) == DO_RESET ) {
   Serial.println("catch");
  #ifdef  WATCHDOG_ENABLE
    iwdg_init(IWDG_PRE_256, 250 ); //watch-dog 250*0.0064 = 1600 ms
    while (1); //stuct here watchdog will get out of here from restart
  #endif//WATCHDOG_ENABLE   
  }

}

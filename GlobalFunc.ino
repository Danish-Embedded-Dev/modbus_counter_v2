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
}
  
/**
    update modbus holding and input register with eeprom store variable
*/

void update_counter_reg(void) {
  //put some data into the registers

  //add coil register
  //  regBank.set(1, 1);           //no coil status used in this module
  //  regBank.set(2, 1);

  //input status register
  //  regBank.set(10001, 1);      //no input status used in this module
  //  regBank.set(10002, 1);


  //adding holding register
//  regBank.set(40001, running_val.device_id);
//  regBank.set(40002, running_val.mod_config);
//  regBank.set(40003, running_val.mod_baud);
//  regBank.set(40004, running_val.net_timeout);
//  regBank.set(40005, running_val.debounce_tm);
//  regBank.set(40006, 0); //zero for normal and 1 for restart
//  unsigned long rtc_time = getEpoch();
//  regBank.set(40007, int((rtc_time)&0xFFFF));     //put Epoch LSB 
//  regBank.set(40008, int((rtc_time>>16)&0xFFFF)); //put Epoch MSB
//  
//  //adding input register
//  regBank.set(30011, running_val.count_1a);
//  regBank.set(30012, running_val.count_1b);
//  regBank.set(30013, running_val.count_1c);
//  regBank.set(30014, int((running_val.lst_epoch_c1)&0xFFFF));  //put last event c_1 Epoch LSB 
//  regBank.set(30015, int((running_val.lst_epoch_c1>>16)&0xFFFF));  //put last event c_1 Epoch MSB 


//  regBank.set(30021, running_val.count_2a);
//  regBank.set(30022, running_val.count_2b);
//  regBank.set(30023, running_val.count_2c);
//  regBank.set(30014, int((running_val.lst_epoch_c2)&0xFFFF));    //put last event c_2 Epoch LSB 
//  regBank.set(30015, int((running_val.lst_epoch_c2>>16)&0xFFFF));  //put last event c_2 Epoch MSB 

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
  
  regBank.set(30001,int((rtc.getTime())&0xFFFF));  //LSB   //use for rtc
  regBank.set(30002,int((rtc.getTime()>>16)&0xFFFF));//MSB
  regBank.set(30003,  int((button1.getcount())&0xFFFF));           //LSB  //for counter 1
  regBank.set(30004,  int((button1.getcount()>>16)&0xFFFF));      //MSB
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

}


///**
//    if user modify the configuration variable then save value to EEPROM
//    @Returns: if eeprom update then true else false
//*/
//bool update_holdingReg() {
//  bool _update = false ;
//
//  //update device id if change by  modbus master
//  if (running_val.device_id != _device->get(40001)) {
//    running_val.device_id = _device->get(40001);
//    EE.eeprom_write_Int(_ADDR_DeviceId, int(running_val.device_id));
//    _update = true;
//  }
//
//  //update modbus configuration if change by  modbus master
//  if (running_val.mod_config != _device->get(40002)) {
//    switch (_device->get(40002)) {
//      case 0:
//        // set to SERIAL wordlenght = 8 parity = none stop bits = 1
//        running_val.mod_config = SERIAL_8N1;
//        regBank.set(40002, SERIAL_8N1);
//        break;
//      case 32:
//        // set to SERIAL wordlenght = 8 parity = none stop bits = 2
//        running_val.mod_config = SERIAL_8N2;
//        regBank.set(40002, SERIAL_8N2);
//        break;
//      case 8:
//        // set to SERIAL wordlenght = 9 parity = none stop bits = 1
//        running_val.mod_config = SERIAL_9N1;
//        regBank.set(40002, SERIAL_9N1);
//        break;
//      case 40:
//        // set to SERIAL wordlenght = 9 parity = none stop bits = 2
//        running_val.mod_config = SERIAL_9N2;
//        regBank.set(40002, SERIAL_9N2);
//        break;
//      case 10:
//        // set to SERIAL wordlenght = 8 parity = even stop bits = 1
//        running_val.mod_config = SERIAL_8E1;
//        regBank.set(40002, SERIAL_8E1);
//        break;
//      case 42:
//        // set to SERIAL wordlenght = 8 parity = even stop bits = 2
//        running_val.mod_config = SERIAL_8E2;
//        regBank.set(40002, SERIAL_8E2);
//        break;
//      case 11:
//        // set to SERIAL wordlenght = 8 parity = old stop bits = 1
//        running_val.mod_config = SERIAL_8O1;
//        regBank.set(40002, SERIAL_8O1);
//        break;
//      case 43:
//        // set to SERIAL wordlenght = 8 parity = old stop bits = 2
//        running_val.mod_config = SERIAL_8O2;
//        regBank.set(40002, SERIAL_8O2);
//        break;
//      default: //use if master modbus enter wrong data
//        // set to SERIAL wordlenght = 8 parity = none stop bits = 1
//        regBank.set(40002, SERIAL_8N1);
//    }
//
//    EE.eeprom_write_Int(_ADDR_Mod_Config, running_val.mod_config);
//    _update = true;
//  }
//
//  //update modbus baud rate if change by  modbus master
//  if (running_val.mod_baud != _device->get(40003)) {
//    switch (_device->get(40003)) {
//      case 1:
//        // set to 2400 baud
//        running_val.mod_baud = 2400;
//        regBank.set(40003, 2400);
//        break;
//      case 2:
//        // set to 4800 baud
//        running_val.mod_baud = 4800;
//        regBank.set(40003, 4800);
//        break;
//      case 3:
//        // set to 9600 baud
//        running_val.mod_baud = 9600;
//        regBank.set(40003, 9600);
//        break;
//      case 4:
//        // set to 19200 baud
//        running_val.mod_baud = 19200;
//        regBank.set(40003, 19200);
//        break;
//      case 5:
//        // set to 38400 baud
//        running_val.mod_baud = 38400;
//        regBank.set(40003, 38400);
//        break;
//    }
//
//    EE.eeprom_write_Int(_ADDR_Mod_Baud, running_val.mod_baud);
//    _update = true;
//  }
//
//  //update network timeout if change by modbus master
//  if (running_val.net_timeout != _device->get(40004)) {
//    running_val.net_timeout = _device->get(40004);
//    EE.eeprom_write_Int(_ADDR_Net_tmout, running_val.net_timeout);
//    _update = true;
//  }
//
//  //update debouncing time if change by modbus master
//  if (running_val.debounce_tm != _device->get(40005)) {
//    running_val.debounce_tm = _device->get(40005);
//    EE.eeprom_write_Int(_ADDR_Debounce_tm, running_val.debounce_tm);
//    _update = true;
//  }
// 
//
//  return _update;
//}
//
///**
//    if user modify the configuration to take action
//*/
//void response_holdingReg() {
//
//  //restart the device if user input 1
//  if (_device->get(40006) == 1  ) {
//#ifdef  WATCHDOG_ENABLE
//    iwdg_init(IWDG_PRE_256, 250 ); //watch-dog 250*0.0064 = 1600 ms
//#endif//WATCH_ENABLE   
//
//    while (1); //stuct here watchdog will get out of here from restart
//  }
//
//  
//  //get current time 
//  if (_device->get(40007) == 1  ) { 
//    unsigned long rtc_time = getEpoch();
//    regBank.set(40007, int((rtc_time)&0xFFFF));     //put Epoch LSB 
//    regBank.set(40008, int((rtc_time>>16)&0xFFFF)); //put Epoch MSB
//  }
//  
//
//}

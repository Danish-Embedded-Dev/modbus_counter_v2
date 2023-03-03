// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions

#ifndef _MODBUS_COUNTER_H
#define _MODBUS_COUNTER_H
#include <Arduino.h>
#include "conf.h"


//--------------------------------------------------
//--include watchdog Rogarclark core library--------
//--------------------------------------------------
#ifdef  WATCHDOG_ENABLE
  #include <libmaple/iwdg.h>
#endif//WATCHDOG_ENABLE
 


//-----------------------------------------
//--include RTC Rogarclark core library-------------
//-----------------------------------------
#ifdef RTC_ENABLE
    #include <RTClock.h> 
#endif//IN_RTC_ENABLE



//-------------------------------------------------
//--include Internal flash library file--------------------
//--------------------------------------------------
#ifdef  INTERNAL_EEPROM_ENABLE
    #include "internal_flash.h"  
    EEPROM_OPERATION  internal_flash; // internal flash instance creation
#endif//INTERNAL_EEPROM_ENABLE



//----------------------------------------------------
//--include library or file related to current project
//--------------------------------------------------
#ifdef  MODBUS_COUNTER  
  #include <modbus.h>
  #include <modbusDevice.h>
  #include <modbusRegBank.h>
  #include <modbusSlave.h>
  
  //Setup the brewtrollers register bank
  //All of the data accumulated will be stored here
  modbusDevice regBank; 
  //Create the modbus slave pointer
  modbusDevice *_device;
  //Create the modbus slave instance
  modbusSlave slave;
#endif//MODBUS_COUNTER


#endif//_MODBUS_COUNTER_H

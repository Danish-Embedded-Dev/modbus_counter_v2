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
 
//--------------------------------------------------
//--include watchdog Rogarclark core library--------
//--------------------------------------------------
#ifdef RESET_STATUS
 #include <libmaple/rcc.h>  // include rcc library for reset status 
#endif//RESET_STATUS
 
//-----------------------------------------
//--include RTC Rogarclark core library-------------
//-----------------------------------------
#ifdef INTERNAL_RTC_ENABLE
    #include <RTClock.h> 
    RTClock rtc (RTCSEL_LSE); // initialise  
#endif//INTERNAL_RTC_ENABLE



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
  #include "LiveStatus.h"
  #include "ButtonDebounce.h"
  
  //Setup the brewtrollers register bank
  //All of the data accumulated will be stored here
  modbusDevice regBank; 
  //Create the modbus slave pointer
  modbusDevice *_device;
  //Create the modbus slave instance
  modbusSlave slave;

  //module online status instance
  LiveStatus  ModuleStatus(STATUS_LED,ACTIVE_TIME);

  //button instance
  ButtonDebounce  button1(INPUT_SW_1,default_var.debounce_tm);  //default milliSeconds debounce
  ButtonDebounce  button2(INPUT_SW_2,default_var.debounce_tm);  //default milliSeconds debounce
#endif//MODBUS_COUNTER


#endif//_MODBUS_COUNTER_H

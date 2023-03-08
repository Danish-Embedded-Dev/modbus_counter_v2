/************************************************************/
/* internal_flash.h                                         */
/*                                                          */
/* Class library for handling internal flash                */
/*                                                          */
/* MODBUS, February 2023                                    */
/************************************************************/
#ifndef INTERNAL_FLASH_H
#define INTERNAL_FLASH_H

#include <Arduino.h> 
#include <EEPROM.h>  
//#include "conf.h"

enum definition 
{  
  CHECKSUM_OK    =  1,
  CHECKSUM_ERROR = -1
};

class EEPROM_OPERATION {
  private: 
  public: 
    void begin(void) ;   
    void set_struct_var(void *obj, uint16_t Objsize);
    int16_t get_struct_var(void *obj, uint16_t Objsize) ;
    
};

#endif //INTERNAL_FLASH_H

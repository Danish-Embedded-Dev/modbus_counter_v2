#include "internal_flash.h"

/*
      @brief  This function sets the ROM portion to be used as EEPROM_X[PORT_1].
*/
void EEPROM_OPERATION::begin(void) {
  //initialize page address
  EEPROM.PageBase0 = 0x801D000;    // Base Address for Page 0...
  EEPROM.PageBase1 = 0x801D800;    // Base Address for Page 1...
  EEPROM.PageSize  = 0x400;        // ROM portion dedicated to be used as EEPROM...
  EEPROM.Status = EEPROM.init();           //initialize eeprom
}

/**
    @brief  Erases PAGE0 and PAGE1 and writes custum structure on the eeprom
    @param  custum structure
    @retval NULL
*/

//        void reset_default(void *obj, uint16_t Objsize) {
//
//        }

/**
    @brief  load structure data to internal flash
    @param  struct instance address, struct instance siz
    @retval NULL
*/

void EEPROM_OPERATION::set_struct_var(void *obj, uint16_t Objsize) {
  //format the pages to write new variable
  EEPROM.Status = EEPROM.format();
  Serial.print("sizeof"); Serial.println(Objsize);
  //casting void object pointer to unsigned integer pointer
  uint16_t *ptr = (uint16_t*)obj; 
  uint16_t checksum=0x00;; 
  
  for (uint16_t i = 0; i < Objsize/2; i++){ 
    checksum ^= *(ptr);         //calculation of checksum of object
    EEPROM.write (i, *(ptr++)); //dump byte to  internal flash 
  }
  EEPROM.write (Objsize/2 + 1 , checksum); //writing checksum at last address 
}



/**
    @brief  read from eeprom and update the structure value if checksum is true
    @param  struct instance address, struct instance size
    @retval -1 if checksum is not matched else 1 on EEPROM_OK
*/
int16_t EEPROM_OPERATION::get_struct_var(void *obj, uint16_t Objsize) { 
   uint16_t checksum = 0x00;
   
  //read whole structure from internal flash and calc checksum
  uint16_t *ptr = (uint16_t*)obj;
  for (uint16_t i = 0; i < Objsize/2; i++){
    EEPROM.read(i, ptr);   //fetching internal flash bytes 
    checksum ^= *(ptr++);  //calculation of checksum of internal flash bytes
  }
     
  //fetch flash stored checksum
  uint16_t str_checksum ;
  EEPROM.read(Objsize/2 + 1, &str_checksum); 
  
  Serial.print("str_checksum:"); Serial.println(str_checksum);
  Serial.print("calc_checksum:");Serial.println(checksum);
  if (str_checksum == checksum) {
    return  CHECKSUM_OK;
  } else {
    return  CHECKSUM_ERROR;
  }

}


 

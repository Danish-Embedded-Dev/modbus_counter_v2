/************************************************************/
/* buttonDebounce.cpp                                       */
/*                                                          */
/* Class library for debounce check of button               */
/*                                                          */
/* MODBUS, FEBRUARY 2023                                    */
/************************************************************/

#include "ButtonDebounce.h" 

//--------------------------------------------------------------
// Constructor
// Puts class into a sane state whenever an instance of the
// class is declared.
//--------------------------------------------------------------

ButtonDebounce::ButtonDebounce(int _pin,unsigned long _debouncePeriod)
{
  swt_pin     = _pin; 
  debouncetm  =_debouncePeriod;
  state       = NOT_PRESSED;
  total_count = 0;  //start count from zero
}

//-----------------------------------------
//accessor function to get button current total count
//para : unsigned long debounce value
//return: total count of button pressed
//---------------------------------------
void  ButtonDebounce::setdebounce(unsigned long debounce_time){
   debouncetm = debounce_time;
}


 

//-----------------------------------------
//accessor function to set button current total count
//return: nothing
//---------------------------------------
void ButtonDebounce::setcount(uint32_t count){
  uint32_t total_count = count;  
}

//-----------------------------------------
//accessor function to set button debounce time
//return: null
//---------------------------------------

uint32_t ButtonDebounce::getcount(){
  return total_count;
}
 
//--------------------------------------------------------------
// process()
//
// Member function that processes timed activity. It takes care
// of timeouts, running / not running etc.
// Returns: nothing
//--------------------------------------------------------------

void ButtonDebounce::process()
{ 
    // FSM belongs here 
      switch(state){
        
          case NOT_PRESSED: 
            if (HAL_SW_RELEASED(swt_pin)) {
              state = NOT_PRESSED;
            }
            else {
              debounce_count = millis();
              state = PARTIAL_PRESS;
            }
            break;//NOT_PRESSED
            
          case PARTIAL_PRESS: 
          
            if (HAL_SW_RELEASED(swt_pin)){
              state = NOT_PRESSED;
            }
            else if (( millis() - debounce_count ) < debouncetm){
              state = PARTIAL_PRESS;
            }
            else {
              total_count++;
              state = DEBOUNCED_PRESS;
            }
            break;//PARTIAL_PRESS
            
          case DEBOUNCED_PRESS: 
            if (HAL_SW_RELEASED(swt_pin)) {
              state = NOT_PRESSED;
            }
            else {
              state = DEBOUNCED_PRESS; 
            }
            break;//DEBOUNCED_PRESS
          
          default: 
            state = NOT_PRESSED; 
            break;
      } //switch
        
}

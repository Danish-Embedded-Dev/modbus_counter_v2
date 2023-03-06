/************************************************************/
/* buttonDebounce.h                                            */
/*                                                          */
/* Class library for debounce of  the button                */
/*                                                          */
/* ENGD2103, November 2022                                  */
/************************************************************/

#ifndef _ButtonDebounce_h_
#define _ButtonDebounce_h_
 
#include "hal.h" 

/*! Indicates that the default (released) state of the button is when the
 *  I/O line reads high. */
#define HAL_SW_RELEASED(_INPUT_PIN)        (digitalRead(_INPUT_PIN))  //return true on released
#define HAL_SW_PRESSED (_INPUT_PIN)       !(digitalRead(_INPUT_PIN))  //return true on pressed


//button states
typedef enum
{
  NOT_PRESSED,
  PARTIAL_PRESS,
  DEBOUNCED_PRESS
} switch_state_t;


class ButtonDebounce {
  public:
             ButtonDebounce(int _pin,unsigned long _debouncePeriod);
    uint32_t getcount();
    void     setcount(uint32_t count);
    void     process();   
 
 private: 
    //button module variables    
    switch_state_t    state;               // buttons state variables
    int             swt_pin;               // use for generic class 
    uint32_t        total_count;           // save total count of button pressed
    unsigned long   debounce_count;        
    unsigned long   debouncetm;            //debounce time after which pressed consider true

};

#endif

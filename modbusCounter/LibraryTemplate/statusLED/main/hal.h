/************************************************************/
/* hal.h                                                    */
/*                                                          */
/* Hardware Adaption Layer (HAL) definitions                */
/* Name / P-number / Date                                   */
/************************************************************/

#ifndef _HAL_H_
#define _HAL_H_

#include <Arduino.h>


//for running state indication
#define STATUS_LED        PC13
 
 
//for button input

//button states
typedef enum
{
  NOT_PRESSED,
  PARTIAL_PRESS,
  DEBOUNCED_PRESS
} switch_state_t;

//input switch pins declaration
#define INPUT_SW_1    PA0 
#define INPUT_SW_2    PA1
#define HAL_SW_RELEASED(_INPUT_PIN)        (digitalRead(_INPUT_PIN))  //return true on released
#define HAL_SW_PRESSED (_INPUT_PIN)       !(digitalRead(_INPUT_PIN))  //return true on pressed

 


void HAL_gpioInit();

#endif

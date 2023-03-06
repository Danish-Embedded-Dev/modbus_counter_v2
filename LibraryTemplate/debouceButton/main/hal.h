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
//input switch pins declaration
#define INPUT_SW_1    PA0 
#define INPUT_SW_2    PA1 

void HAL_gpioInit();

#endif

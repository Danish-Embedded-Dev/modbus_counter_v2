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
 

void HAL_gpioInit();

#endif

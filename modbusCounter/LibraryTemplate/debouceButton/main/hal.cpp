/************************************************************/
/* hal.cpp                                                  */
/*                                                          */
/* Hardware Adaption Layer (HAL) implementation             */
/* Name / P-number / Date                                   */
/************************************************************/

#include "hal.h"

void HAL_gpioInit()
{
 //make output for status led
   pinMode(STATUS_LED,OUTPUT);

 //make input pullup
   pinMode(INPUT_SW_1,INPUT_PULLUP);
   pinMode(INPUT_SW_2,INPUT_PULLUP);
  
}

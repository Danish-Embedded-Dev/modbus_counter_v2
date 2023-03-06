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
  
}

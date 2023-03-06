/************************************************************/
/* liveStatus.h                                             */
/*                                                          */
/* Class library for online status of device                */
/*                                                          */
/* MODBUS, February 2023                                    */
/************************************************************/

#include "LiveStatus.h"


/*
 * contructor
 * @param idle_time in milli second    
 */
LiveStatus::LiveStatus(int _pin,int active_tm)
{ 
  _status_led    =   _pin;
  active_time    =   active_tm;
  event_start_tm = - active_tm;  //it will only trigger when set by set function
  state = 0;
}

//--------------------------------------------------------------
// process()
//
// Member function that set the status time   
// Returns: nothing
//--------------------------------------------------------------
void LiveStatus::set()
{
  event_start_tm = millis();
}

//--------------------------------------------------------------
// process()
//
// Member function that processes timed activity. It takes care
// of timeouts, running / not running etc.
// Returns: nothing
//--------------------------------------------------------------

void LiveStatus::process()
{
    //once set will be active state 0 for active_time period
    if(millis()- event_start_tm < active_time){ 
      state = 0 ;
    }
   
    // FSM belongs here
    switch (state)
    { 
        case 0:
          HAL_statusOn(_status_led);  
          state = 1;
          break;
         
        case 1: 
          HAL_statusOff(_status_led);
          break;
    }  
}

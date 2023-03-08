/************************************************************/
/* liveStatus.h                                             */
/*                                                          */
/* Class library for online status of device                */
/*                                                          */
/* MODBUS, February 2023                                    */
/************************************************************/

#ifndef _LiveStatus_h_
#define _LiveStatus_h_ 

#include <Arduino.h> 

#define HAL_statusOn(_status_pin)   digitalWrite(_status_pin,HIGH)
#define HAL_statusOff(_status_pin)  digitalWrite(_status_pin,LOW)

class LiveStatus {
  public:
                     LiveStatus(int _pin,int active_tm);  //constructor
    void             set_timeout(int active_tm);
    void             set();
    void             process();

  private:
    int              _status_led;
    int              state;
    unsigned int     active_time;
    unsigned long    event_start_tm;
};

#endif

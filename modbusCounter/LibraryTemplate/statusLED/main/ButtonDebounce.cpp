///************************************************************/
///* RedBlinker.cpp                                           */
///*                                                          */
///* Class library for debounce check of button               */
///*                                                          */
///* ENGD2103, November 2022                                  */
///************************************************************/
//
//#include "ButtonDebounce.h"
//#include "hal.h"
//
//
////--------------------------------------------------------------
//// Constructor
//// Puts class into a sane state whenever an instance of the
//// class is declared.
////--------------------------------------------------------------
//
//ButtonDebounce::ButtonDebounce(int _pin)
//{ 
//  swt_pin = _pin;
//  module_delay = 15;
//  state = 0;
//}
//
//
////-----------------------------------------
////accessor function to get button current state
////---------------------------------------
//switch_state_t ButtonDebounce::getstate(){
//  return state;
//}
////-----------------------------------------
////accessor function to set module enable/disable
////---------------------------------------
//
//void ButtonDebounce::setmodule(bool val)
//{ 
// init_module1_clock = val ;
//}
////--------------------------------------------------------------
//// process()
////
//// Member function that processes timed activity. It takes care
//// of timeouts, running / not running etc.
//// Returns: nothing
////--------------------------------------------------------------
//
//byte ButtonDebounce::process(byte count)
//{ 
//    // FSM belongs here
//    if (actionTask()) {
//      switch(state){
//          case NOT_PRESSED: 
//            if (HAL_SW_RELEASED(swt_pin)) state = NOT_PRESSED;
//            else {
//              debounce_count = millis();
//              state = PARTIAL_PRESS;
//            }
//            break;
//          case PARTIAL_PRESS: 
//            if (HAL_SW_RELEASED(swt_pin)) state = NOT_PRESSED;
//            else if ((millis()-debounce_count) < debounce) state = PARTIAL_PRESS;
//            else state = DEBOUNCED_PRESS;
//            break;
//          case DEBOUNCED_PRESS: 
//            if (HAL_SW_RELEASED(swt_pin)) {
//              count++;
//              state = NOT_PRESSED;
//            }
//            else {
//              state = DEBOUNCED_PRESS; 
//            }
//            break;
//          
//          default: 
//            state = NOT_PRESSED; 
//            break;
//      }   
//   }
//   return count;
//}
//
////--------------------------------------------------------------
//// actionTask
//// Function to perform the timing. 
////--------------------------------------------------------------
//
//bool ButtonDebounce::actionTask()
//{
//  if (init_module1_clock) {
//      module_delay = 15;
//      module_time=millis();
//      module_doStep=false;
//      init_module1_clock=false;
//      state = NOT_PRESSED;
//    }
//    else {
//      unsigned long m=millis();
//      if ( ( (long)(m - module_time) ) > module_delay ) {
//        module_time = m; module_doStep = true;
//      }
//      else module_doStep = false;
//    }
//  return module_doStep;
//}

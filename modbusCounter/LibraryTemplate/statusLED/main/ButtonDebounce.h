///************************************************************/
///* buttonDebounce.h                                            */
///*                                                          */
///* Class library for debounce of  the button                */
///*                                                          */
///* ENGD2103, November 2022                                  */
///************************************************************/
//
//#ifndef _ButtonDebounce_h_
//#define _ButtonDebounce_h_
// 
//#include "hal.h" 
//
//class ButtonDebounce {
//  public:
//    ButtonDebounce(int _pin);
//    byte process(byte count);
//    void setmodule(bool val);
//    bool actionTask(); 
//    switch_state_t getstate();
// 
// private: 
//    //module1 variables    
//    switch_state_t    state;   // buttons state variables
//    int swt_pin; //use for generic class 
//    bool init_module1_clock;
//    unsigned long module_time, module_delay;
//    bool module_doStep;
//    unsigned long debounce_count;
//    #define debounce  500         // debounce duration
//
//};
//
//#endif

#include "main.h"

void setup() {
  
#ifdef  WATCHDOG_ENABLE   
                              iwdg_init(IWDG_PRE_256,3500); //watch-dog 5000*0.0064 = 32000 ms
#endif//WATCH_ENABLE

#ifdef DEBUGOUT
        Serial.begin(9600);
//        while(!Serial); 
#endif//DEBUGOUT
 
#ifdef INTERNAL_EEPROM_ENABLE   
        //initialize internal flash for storage
        internal_flash.begin();
        
        //get structure from internal flash
        if(internal_flash.get_struct_var(&running_var,sizeof(running_var))){
          DEBUG_PRINTLN("EEPROM_CHECK : OK"); 
        }else{
          DEBUG_PRINTLN("EEPROM_CHECK : ERR"); 
          internal_flash.set_struct_var(&default_var,sizeof(default_var)); //set default to flash
        }
#endif//INTERNAL_EEPROM_ENABLE

#ifdef  RESET_STATUS
        //check the reset cause
        uint32_t rcc_csr_value = RCC_BASE->CSR;
      
        if ((rcc_csr_value & RCC_CSR_PORRSTF) != 0) { // POR/PDR reset
          // if Power on reset then reset  variable to zero
          SRAM_Var[_cnt_1]     = 0;
          SRAM_Var[_cnt_2]     = 0; 
        } else {
          running_var.count_1 = SRAM_Var[_cnt_1];
          running_var.count_2 = SRAM_Var[_cnt_2]; 
        } 
        
        // Clear the reset flags in the RCC_CSR register
        //with Reset Management Value Flag
        RCC_BASE->CSR |= RCC_CSR_RMVF;
  
#endif//RESET_STATUS

#ifdef MODBUS_COUNTER
        //Pins Configuration
        gpioInit();
        
        //Assign the modbus device ID.  
        regBank.setId(running_var.device_id);

        //initialize all required registers
        init_reg();  
        
        /*
        Assign the modbus device object to the protocol handler
        This is where the protocol handler will look to read and write
        register data.  Currently, a modbus slave protocol handler may
        only have one device assigned to it.
        */
        slave._device = &regBank; 
      
        // Initialize the serial port for coms at 9600 baud  
        slave.setBaud(running_var.mod_baud,running_var.mod_config);  

        //add debounce time which store in flash
        button1.setdebounce(running_var.debounce_tm);
        button2.setdebounce(running_var.debounce_tm);

        //add counter offset which store in SRAM
        button1.setcount(running_var.count_1);
        button2.setcount(running_var.count_2);

        //add live status active time period 
        ModuleStatus.set_timeout(running_var.net_timeout);
        
#endif //MODBUS_COUNTER

}
  
void loop() { 
  
#ifdef  WATCHDOG_ENABLE    
     //Feeding watch dog
     iwdg_feed(); 
#endif//WATCH_ENABLE   

#ifdef  MODBUS_COUNTER    
    //response to register values
    response_holdingReg(); 
    //take action if update register by modbus master required
     update_holdingReg();
    //put current data into the registers
    update_counter_reg();

    //setting led if there is any message in serial  
    if(slave.checkSerial()>1)    
      ModuleStatus.set();     //start led active for ACTIVE_TIME in ms 
    
    
    button1.process();       //handle process of button1 activity
    button2.process();       //handle process of button2 activity
    ModuleStatus.process();  //handle process of module live activity
    slave.run();             //handle process of modbus module activity
#endif//MODBUS_COUNTER   

#ifdef INTERNAL_RTC_ENABLE
    running_var.count_1 =  button1.getcount();
    running_var.count_2 =  button2.getcount();
    SRAM_Var[_cnt_1]    =  running_var.count_1; //update sram variable
    SRAM_Var[_cnt_2]    =  running_var.count_2; //update sram variable
#endif//INTERNAL_RTC_ENABLE
}

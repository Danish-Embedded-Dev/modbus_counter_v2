//working reference https://rambutan.readthedocs.io/projects/librambutan/en/latest/libmaple/api/rcc.html
//theory reference https://micromouseonline.com/2012/03/29/stm32-reset-source/

#include <libmaple/iwdg.h>  //include watchdog library
#include <libmaple/rcc.h>  // include rcc library for reset status

uint32_t SRAM_Var[3] __attribute__((section(".noinit")));
#define _cnt_1  0
#define _cnt_2  1 
#define _epoch  2

uint32_t counter_1, counter_2, epoch;

void setup() {
  iwdg_init(IWDG_PRE_256, 3500);          //setup watch-dog to 5000*0.0064 = 32000 ms

  // Print the values to verify that they were read correctly
  Serial.begin(9600);
  while (!Serial);

  //check the reset cause
  uint32_t rcc_csr_value = RCC_BASE->CSR;

  if ((rcc_csr_value & RCC_CSR_PORRSTF) != 0) { // POR/PDR reset
    // if Power on reset then reset  variable to zero
    SRAM_Var[_cnt_1]     = 0;
    SRAM_Var[_cnt_2]     = 0;
    SRAM_Var[_epoch]     = 0;
  } else {
    counter_1 = SRAM_Var[_cnt_1];
    counter_2 = SRAM_Var[_cnt_2];
    epoch     = SRAM_Var[_epoch];
  }
  //  } else if ((rcc_csr_value & RCC_CSR_PINRSTF) != 0) {
  //    // NRST pin reset
  //    Serial.print("NRST");
  //  } else if ((rcc_csr_value & RCC_CSR_SFTRSTF) != 0) {
  //    // software reset
  //    Serial.print("soft");
  //  } else if ((rcc_csr_value & RCC_CSR_IWDGRSTF) != 0) {
  //    // independent watchdog reset
  //  } else if ((rcc_csr_value & RCC_CSR_WWDGRSTF) != 0) {
  //    // window watchdog reset
  //    Serial.print("window watchdog");
  //  } else if ((rcc_csr_value & RCC_CSR_LPWRRSTF) != 0) {
  //    // low-power reset
  //    Serial.print("low power");
  //  }

  // Clear the reset flags in the RCC_CSR register
  //with Reset Management Value Flag
  RCC_BASE->CSR |= RCC_CSR_RMVF;
}

void loop() {
//  iwdg_feed(); //Feeding watch dog

  Serial.print("Counter_1: ");
  Serial.print(SRAM_Var[_cnt_1]);
  Serial.print(" , Counter_2: ");
  Serial.print(SRAM_Var[_cnt_2]);
  Serial.print(" , epouchtime: ");
  Serial.println(SRAM_Var[_epoch]);
  counter_1++;
  counter_2++;
  epoch++;
  SRAM_Var[_cnt_1] =  counter_1;
  SRAM_Var[_cnt_2] =  counter_2;
  SRAM_Var[_epoch] =  epoch;
  delay(500);
 
}

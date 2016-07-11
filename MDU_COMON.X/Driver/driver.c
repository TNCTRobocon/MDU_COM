#include "../Setting/configuration.h"
#include "ports.h"
#include "driver.h"
#include "pwm.h"
#include "encoder.h"
#include "uart.h"
#include "eeprom.h"



bool driver_setup(){
    
    //クロック確認
#if !defined(IS_SLIM)
    while (OSCCONbits.LOCK != 1);//PLL Lock
#endif
    //周辺機器(優先度高)
    ports_setup();
    //システム(優先度高)
   //eeprom_setup();
    //周辺機器
    pwm_setup();
    encoder_setup();
    
    uart_setup();
    
    
    pwm_shutdown(false); 
    return false;
}


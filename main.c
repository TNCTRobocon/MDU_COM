#include "Setting/configuration.h"
#include "Driver/driver.h"
#include "System/shell.h"
#include "Driver/uart.h"
#include "System/system.h"
#include <stdbool.h>
#include <stdlib.h>
 
#include "Driver/timer.h"

int main(){

    driver_setup();
    system_setup();
    
    

    for (;;){
        system_process();
    }
    __asm("reset");//初期化
    return 0;//決してここまで来ない
}

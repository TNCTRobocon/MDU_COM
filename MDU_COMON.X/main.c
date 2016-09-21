#include "Setting/configuration.h"
#include "Task/task.h"
#include "Driver/driver.h"
#include "Driver/uart.h"
#include "Application/motor.h"
#include <stdbool.h>
#include <stdlib.h>
 
int main(){  
    driver_setup();
    task_setup();
    
    timer_enable(true);
    //uart_stop();                        //test
    for (;;){
        process_old();
    }
    __asm("reset");//初期化
    return 0;//決してここまで来ない
}
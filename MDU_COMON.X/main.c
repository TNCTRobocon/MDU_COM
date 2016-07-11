#include "Setting/configuration.h"
#include "Driver/driver.h"
#include "Task/task.h"
#include "Driver/uart.h"




int main(){
    
    driver_setup(); 
    task_setup();
    for (;;){
        process();
    }
    __asm("reset");//初期化
    return 0;//決してここまで来ない
}
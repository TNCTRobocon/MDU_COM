#include "Setting/configuration.h"
#include "Driver/driver.h"
#include "Task/task.h"




int main(){
    driver_setup(); 

    task_setup();
    
    
    
    __asm("reset");//メモリ等に問題があり初期化
    return 0;//決してここまで来ない
}
#include "system.h"
#include "shell.h"
#include "../Driver/uart.h"
#include "../Setting/configuration.h"

void system_setup(){
    shell_init();   
}

void system_process(){
    char buf[CMD_LENGTH];
    if (uart_have('\r')){
        uart_gets(buf,sizeof(buf));
        shell_system(buf);
    }   
}
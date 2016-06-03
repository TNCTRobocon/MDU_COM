#include "task.h"
#include "../Driver/uart.h"
#include "../Driver/io.h"
#include <string.h>
#include <stdlib.h>
#include "system.h"



#define forever() for(;;)

#define LINE_SIZE       (32)

void task_setup() {

    system_setup();
    io_setup();
    transmit_init();
}

void process(){
    transmit();
    
}


void transmit_init() {
    //TODO 


}

void transmit() {
    char line[LINE_SIZE];
    if (uart_have('\r')) {
        uart_gets(line, LINE_SIZE);
        system_decode(line);
    }



}


#include "error.h"
#include "../Driver/uart.h"
#include <stddef.h>

static PSV char text_error[]="Error:";
static PSV char *text_detail[]={
    "*",            //0
    "Unknown",      
    "NotExist",     //2
    "NotSurpport",
    "NotExcute",    //4
    "NotDirectory", 
    "NotFoundOut",  //6
    "FewInputs",    
    "FileTypeNone", //8
    "FilETypeDirecotory",
    "NotAccess",    //10
    "InputFraud"
            

};


int errno;

int error_print(error_t err){
    uart_bufs(text_error);
    uart_putl(text_detail[(int16_t)err]);
    errno=err;
    return -(int)err;//エラーコードはマイナスである。
}

